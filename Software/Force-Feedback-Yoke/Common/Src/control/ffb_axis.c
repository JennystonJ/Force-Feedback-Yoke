/*
 * ffb_axis.c
 *
 *  Created on: Apr 27, 2026
 *      Author: Jennyston
 */

#include <control/ffb_axis.h>
#include <math.h>

// Private function prototypes
// Initialization prototypes
static void FFBAxis_MotorInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);

static void FFBAxis_VelocityControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config);
static void FFBAxis_PositionControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config);
static void FFBAxis_MotionControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config);

static void FFBAxis_VelocityEstimatorInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config);
static void FFBAxis_LoadCellInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);
static void FFBAxis_AxisGeometryInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);
static void FFBAxis_AxisLimitsInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);
static void FFBAxis_FFBInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);
static void FFBAxis_FFBAssistInit(FFBAxis_t *axis, const FFBAxisConfig_t *config);

static void FFBAxis_KinematicsUpdate(FFBAxis_t *axis, float deltaTimeMs);
static void FFBAxis_ProcessHoming(FFBAxis_t *axis, float deltaTime);

void FFBAxis_Init(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	axis->motor = config->hardware.motor;
	axis->encoder = config->hardware.encoder;
	axis->loadCell = config->hardware.loadCell;

	axis->controlMode = AXIS_MOTION_CONTROL_MODE_TORQUE;

	FFBAxis_AxisLimitsInit(axis, config);

	FFBHome_Init(&axis->home, &config->home);

	FFBAxis_VelocityEstimatorInit(axis, config);

	FFBAxis_MotorInit(axis, config);

	FFBAxis_VelocityControlInit(axis, config);
	FFBAxis_PositionControlInit(axis, config);
	FFBAxis_MotionControlInit(axis, config);

	FFBAxis_LoadCellInit(axis, config);
	FFBAxis_AxisGeometryInit(axis, config);
	FFBAxis_FFBInit(axis, config);
	FFBAxis_FFBAssistInit(axis, config);

	// Assign initial velocity value (required for acceleration calculations)
	// TODO: Obtain velocity in radians
	axis->kinematics.velocity = Motor_GetVelocity(axis->motor);

	LowPassFilter_Init(&axis->lpfAccel, config->vel.lpfAccelAlpha);
}

void FFBAxis_StartCalibration(FFBAxis_t *axis) {
	axis->mode = FFB_AXIS_MODE_CAL;
	Motor_StartCalibration(axis->motor);
}

bool FFBAxis_IsCalibrationDone(FFBAxis_t *axis) {
	return axis->mode != FFB_AXIS_MODE_CAL;
}

//void FFBAxis_UpdateVelocityControl(FFBAxis_t *axis, float targetVelocity,
//		float deltaTime) {
//	VelocityControl_SetRadSTarget(&axis->velControl, targetVelocity);
//	float actualVelocity = Encoder_GetVelocityRadPerS(axis->encoder);
//	float torque = VelocityControl_CalcTorque(&axis->velControl, actualVelocity,
//			deltaTime);
//	Motor_SetTorque(axis->motor, torque);
//}

void FFBAxis_StartHoming(FFBAxis_t *axis) {
	AxisLimits_SetOperatingMaxTorque(&axis->limits,
			FFBHome_GetSearchMotorTorque(&axis->home));
	FFBHome_Start(&axis->home);
	axis->mode = FFB_AXIS_MODE_HOMING;
}

bool FFBAxis_IsHomingDone(FFBAxis_t *axis) {
	return axis->mode != FFB_AXIS_MODE_HOMING;
}

void FFBAxis_Update(FFBAxis_t *axis, float deltaTimeMs) {

	FFBAxis_KinematicsUpdate(axis, deltaTimeMs);

	switch(axis->mode){
		case FFB_AXIS_MODE_DISABLED:
			// Do nothing
			break;
		case FFB_AXIS_MODE_IDLE:
			// Do nothing
			break;
		case FFB_AXIS_MODE_FFB_ACTIVE:
			float ffbTorque = FFB_Update(&axis->ffb, &axis->kinematics,
					deltaTimeMs/1000.0f);
//			float assistTorque = FFBAssist_Calc(&axis->assist, &axis->kinematics,
//					deltaTimeMs/1000.0f);
			float netTorque = ffbTorque;// + assistTorque;

			MotionControl_SetTorqueCommand(&axis->motionControl,
					netTorque, axis->limits.operating.maxTorque);
			break;
		case FFB_AXIS_MODE_CAL:
			break;
		case FFB_AXIS_MODE_HOMING:
			FFBAxis_ProcessHoming(axis, deltaTimeMs/1000.0f);
			break;
		default:
			// Do nothing
	}

	FFBAxis_MotionControlUpdate(axis, deltaTimeMs/1000.0f);
}

void FFBAxis_MotionControlUpdate(FFBAxis_t *axis, float deltaTime) {
	//	switch (axis->controlMode) {
	//		case AXIS_MOTION_CONTROL_MODE_OFF:
	//			Motor_SetTorque(axis->motor, 0);
	//			break;
	//		case AXIS_MOTION_CONTROL_MODE_TORQUE:
	//			// Do nothing, handled by motor update
	//			break;
	//		case AXIS_MOTION_CONTROL_MODE_VELOCITY:
	//			float torque = VelocityControl_CalcTorque(&axis->velControl,
	//					axis->kinematics.velocity,
	//					deltaTime);
	//			Motor_SetTorque(axis->motor, torque);
	//			break;
	//		default:
	//			// Do nothing
	//	}

	TorqueControlCommand_t torqueCommand =
			MotionControl_CalcTorque(&axis->motionControl, &axis->kinematics,
					deltaTime);
	FFBAxis_SetAxisTorque(axis, &torqueCommand);
}

static void FFBAxis_KinematicsUpdate(FFBAxis_t *axis, float deltaTimeMs) {
	// Convert and update position
	axis->kinematics.position =	Encoder_GetRad(axis->encoder);

	// Store previous velocity for acceleration calculation
	float preVelocity = axis->kinematics.velocity;
	// Convert and update velocity
//	VelocityEstimator_Update(&axis->ve, axis->kinematics.position,
//			deltaTimeMs/1000.0f);
//	axis->kinematics.velocity =
//			VELOCITY_EDGE_POS_WEIGHT*Encoder_GetVelocityRadPerS(axis->encoder) +
//			(1 - FFB_AXIS_VELOCITY_EDGE_POS_WEIGHT) *
//			(VelocityEstimator_GetVelocity(&axis->ve)/
//					(Encoder_GetCountPerRev(axis->encoder)/65536));
	axis->kinematics.velocity = VelocityEstimator_GetVelocity(&axis->ve);

	// Acceleration calculations
	float rawAccel = (axis->kinematics.velocity - preVelocity) /
			deltaTimeMs/1000.0f;
	axis->kinematics.acceleration = rawAccel;
	//LowPassFilter_Update(&axis->lpfAccel, rawAccel);

	// Update and covert torque units
	axis->kinematics.motorTorque = Motor_GetMeasuredTorque(axis->motor);
	axis->kinematics.loadCellTorque = AxisGeometry_YokeEffortToMotorTorque(&axis->geom,
			LoadCell_GetValue(axis->loadCell));// - axis->kinematics.motorTorque;
}

void FFBAxis_ControlISR(FFBAxis_t *axis, float deltaTimeMs) {
	Encoder_Update(axis->encoder, deltaTimeMs);
	VelocityEstimator_Update(&axis->ve, Encoder_GetRad(axis->encoder),
			deltaTimeMs/1000.0f);
	Motor_Update(axis->motor, deltaTimeMs);

	if(axis->mode == FFB_AXIS_MODE_CAL && !Motor_IsCalibrationRunning(axis->motor)) {
		// Update axis mode when calibration is done
		axis->mode = FFB_AXIS_MODE_IDLE;
	}
}

FFBAxisStatus_e FFBAxis_SetFFBOn(FFBAxis_t *axis) {

	FFBAxisMode_e *mode = &axis->mode;

	if(*mode == FFB_AXIS_MODE_DISABLED ||
			*mode == FFB_AXIS_MODE_IDLE ||
			*mode == FFB_AXIS_MODE_FFB_ACTIVE) {
		*mode = FFB_AXIS_MODE_FFB_ACTIVE;
		AxisLimits_SetOperatingMaxTorque(&axis->limits, 0.5);
		return FFB_AXIS_STATUS_OK;
	}
	else {
		return FFB_AXIS_STATUS_ERROR;
	}
}

FFBAxisStatus_e FFBAxis_SetFFBOff(FFBAxis_t *axis) {

	FFBAxisMode_e *mode = &axis->mode;

	if(*mode == FFB_AXIS_MODE_FFB_ACTIVE ||
			*mode == FFB_AXIS_MODE_IDLE) {
		*mode = FFB_AXIS_MODE_IDLE;
		return FFB_AXIS_STATUS_OK;
	}
	else {
		return FFB_AXIS_STATUS_ERROR;
	}
}

AxisRange_t FFBAxis_GetSafeAxisPositionRange(FFBAxis_t *axis) {
	return axis->limits.safety.positionRange;
}

float FFBAxis_GetSafeMaxTorque(FFBAxis_t *axis) {
	return axis->limits.safety.maxTorque;
}

MotionControl_t *FFBAxis_GetMotionControl(FFBAxis_t *axis) {
	return &axis->motionControl;
}

void FFBAxis_ApplyMotionCommand(FFBAxis_t *axis,
		const MotionControlCommand_t *command, float deltaTime) {
	MotionControl_SetCommand(&axis->motionControl, command);
}

void FFBAxis_SetAxisVelocity(FFBAxis_t *axis,
		const MotionControlCommand_t *command) {
//	Motor_SetTorqueLimit(axis->motor, command->torqueLimit);
//	VelocityControl_SetAccelerationLimit(&axis->velControl,
//			command->accelerationLimit);
//	VelocityControl_SetRadSTarget(&axis->velControl, command->data.velocityTarget);
//	axis->controlMode = AXIS_MOTION_CONTROL_MODE_VELOCITY;
}


void FFBAxis_SetAxisTorque(FFBAxis_t *axis,
		const TorqueControlCommand_t *torqueCommand) {
	axis->controlMode = AXIS_MOTION_CONTROL_MODE_TORQUE;

	Motor_SetTorqueLimit(axis->motor,
			fminf(AxisLimits_GetSafetyMaxTorque(&axis->limits),
					torqueCommand->torqueLimit));

	float limitedTorque = AxisLimits_LimitTorque(&axis->limits,
			&axis->kinematics, torqueCommand->torqueTarget);
	Motor_SetTorque(axis->motor, limitedTorque);
}

void FFBAxis_SetForces(FFBAxis_t *axis, const FFBForces_t *forces) {

	FFB_SetForces(&axis->ffb, *forces);
	axis->controlMode = AXIS_MOTION_CONTROL_MODE_TORQUE;
}

VelocityControl_t *FFBAxis_GetVelocityControl(FFBAxis_t *axis) {
	return &axis->velControl;
}

const AxisKinematics_t *FFBAxis_GetAxisKinematics(FFBAxis_t *axis) {
	return &axis->kinematics;
}

AxisLimits_t *FFBAxis_GetAxisLimits(FFBAxis_t *axis) {
	return &axis->limits;
}



static void FFBAxis_MotorInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
//	Motor_InitVelocityEncoder(axis->motor, config->hardware.encoder);
//	Motor_SetVelocityLoopFreqDivider(axis->motor, config->vel.loopDivider);
//	Motor_SetVelocityFilterAlpha(axis->motor, config->vel.lpfAlpha);
}

static void FFBAxis_VelocityControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config) {
	const VelocityConfig_t *velConfig = &config->vel;

	VelocityControl_Init(&axis->velControl);
	PID_t *velPid = VelocityControl_GetVelocityPID(&axis->velControl);
	PID_SetGains(velPid, velConfig->kp, velConfig->ki,
			velConfig->kd);
	PID_SetIntegralEpsilon(velPid, velConfig->epsilon);
	PID_SetIntegralLimit(velPid, velConfig->integralLimit);
}

static void FFBAxis_PositionControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config) {
	const PositionConfig_t *posConfig = &config->pos;

	PositionControl_Init(&axis->posControl);
	PID_t *posPid = PositionControl_GetPositionPID(&axis->posControl);
	PID_SetGains(posPid, posConfig->kp, posConfig->ki, posConfig->kd);
	PID_SetIntegralEpsilon(posPid, posConfig->epsilon);
	PID_SetIntegralLimit(posPid, posConfig->integralLimit);
}

static void FFBAxis_MotionControlInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config) {
	MotionControl_Init(&axis->motionControl, &axis->velControl, &axis->posControl);
}

static void FFBAxis_VelocityEstimatorInit(FFBAxis_t *axis,
		const FFBAxisConfig_t *config) {
	VelocityEstimator_Init(&axis->ve, Encoder_GetRad(axis->encoder),
			config->ve.kP, config->ve.kI);
}

static void FFBAxis_LoadCellInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	LoadCell_SetLowPassAlpha(axis->loadCell, config->loadCell.lpfAlpha);
	LoadCell_SetConversionConstant(axis->loadCell,
			config->loadCell.conversionConstant);
}

static void FFBAxis_AxisGeometryInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	axis->geom.yokeEffortToMotorTorque = config->geom.yokeEffortToMotorTorque;
	axis->geom.posToRad = config->geom.posToRad;
}

static void FFBAxis_AxisLimitsInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	axis->limits.safety.maxTorque = config->safeLimits.maxTorque;
	axis->limits.safety.positionRange = config->safeLimits.positionRange;

	axis->limits.operating.maxTorque = 0.0f;
	axis->limits.operating.positionRange = config->safeLimits.positionRange;

	axis->limits.stopperSpring = config->stopper.springGain;
	axis->limits.stopperDamper = config->stopper.damperGain;
}

static void FFBAxis_FFBInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	FFB_Init(&axis->ffb);
	//	FFB_SetLockGains(&axis->ffb, config->ffb.lockKp, config->ffb.lockKd);
	//	FFBForces_t homeCenterForces = {
	//			.constantForce = 0.0f,
	//			.springForce = 0.0f,
	//			.damperForce = 0.0f
	//	};
	//	FFB_SetHomeCenterForces(&axis->ffb, homeCenterForces);

	// FFB Assist setup
	//	FFBAssist_t *ffbAssist = FFB_GetFFBAssist(&axis->ffb);
	//	FFBAssist_SetGain(ffbAssist, config->assist.assistGain);
	//	FFBAssist_SetAccelerationGain(ffbAssist, config->assist.accelGain);
	//	FFBAssist_SetVelocityGain(ffbAssist, config->assist.velGain);
	//	FFBAssist_SetVelocitySmallCompensation(ffbAssist, config->assist.velSmallComp);
}

static void FFBAxis_FFBAssistInit(FFBAxis_t *axis, const FFBAxisConfig_t *config) {
	FFBAssist_t *assist = &axis->assist;
	FFBAssist_Init(assist);
	FFBAssist_SetGain(assist, config->assist.assistGain);
	FFBAssist_SetAccelerationGain(assist, config->assist.accelGain);
	FFBAssist_SetVelocityGain(assist, config->assist.velGain);
	FFBAssist_SetVelocitySmallCompensation(assist, config->assist.velSmallComp);
}

static void FFBAxis_ProcessHoming(FFBAxis_t *axis, float deltaTime) {
	MotionControlCommand_t command = FFBHome_CalcMotionCommand(&axis->home,
			&axis->kinematics,
			VelocityControl_GetAccelerationTarget(&axis->velControl),
			deltaTime);

	MotionControl_SetCommand(&axis->motionControl, &command);


	if(FFBHome_IsHomingDone(&axis->home)) {

		AxisRange_t discoveredRange = FFBHome_GetDiscoveredRange(&axis->home);

		// Calculate distance
		float distance = discoveredRange.max - discoveredRange.min;
		// Calculate distance center
		float center = distance / 2.0f;
		// Calculate offset
		float offset = axis->kinematics.position - center;
		Encoder_SetCount(axis->encoder, offset);


		AxisRange_t newRange = {
				.min = -center,
				.max = center
		};
		AxisLimits_SetSafetyPositionRange(&axis->limits, newRange);

		axis->controlMode = AXIS_MOTION_CONTROL_MODE_OFF;
		axis->mode = FFB_AXIS_MODE_IDLE;
	}
}
