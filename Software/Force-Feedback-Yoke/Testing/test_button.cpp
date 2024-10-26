
#include "gtest/gtest.h"
#include "button.h"
#include <stdbool.h>

int mock_ButtonSet(Button_t *button) {
	return 1;
}

int mock_ButtonReset(Button_t *button) {
	return 0;
}

TEST(ButtonTest, ButtonProcessIntResetSteadyCount) {
	// Arrange
	Button_t button;
	button.ButtonReadState = &mock_ButtonSet;
	button.ButtonStateChangedCallback = NULL;
	button.pressed = false;
	button.previouslyPressed = false;
	button.steadyCount = 0;
	button.state = BUTTON_STATE_IDLE;

	// Act
	// Trigger changed state (transition to BUTTON_STATE_DEBOUNCING)
	ButtonProcessInt(&button);
	// Increment steady count by 1
	ButtonProcessInt(&button);
	// Reset count by changing button state
	button.ButtonReadState = &mock_ButtonReset;
	ButtonProcessInt(&button);

	// Assert
	ASSERT_EQ(button.steadyCount, 0);
}

TEST(ButtonTest, ButtonProcessIntIncrementSteadyCount) {
	// Arrange
	Button_t button;
	button.ButtonReadState = &mock_ButtonSet;
	button.ButtonStateChangedCallback = NULL;
	button.pressed = false;
	button.previouslyPressed = false;
	button.steadyCount = 0;
	button.state = BUTTON_STATE_IDLE;

	// Act
	// Trigger changed state (transition to BUTTON_STATE_DEBOUNCING)
	ButtonProcessInt(&button);
	// Increment steady count by 1 by maintaining button state
	ButtonProcessInt(&button);

	// Assert
	ASSERT_EQ(button.steadyCount, 1);
}

TEST(ButtonTest, ButtonProcessIntRegisterPressed) {
	// Arrange
	Button_t button;
	button.ButtonReadState = &mock_ButtonSet;
	button.ButtonStateChangedCallback = NULL;

	// Start off as not pressed
	button.pressed = false;
	button.previouslyPressed = false;

	button.steadyCount = 0;
	button.state = BUTTON_STATE_IDLE;

	// Act
	// Trigger changed state (transition to BUTTON_STATE_DEBOUNCING)
	ButtonProcessInt(&button);
	// Increment steady count until BUTTON_MAX_STEADY_COUNT is reached
	for(int i = 0; i < BUTTON_MAX_STEADY_COUNT; i++) {
		ButtonProcessInt(&button);
	}

	// Assert
	ASSERT_EQ(button.pressed, 1);
}

TEST(ButtonTest, ButtonProcessIntRegisterNotPressed) {
	// Arrange
	Button_t button;
	button.ButtonReadState = &mock_ButtonReset;
	button.ButtonStateChangedCallback = NULL;

	// Start off as button pressed
	button.pressed = true;
	button.previouslyPressed = true;

	button.steadyCount = 0;
	button.state = BUTTON_STATE_IDLE;

	// Act
	// Trigger changed state (transition to BUTTON_STATE_DEBOUNCING)
	ButtonProcessInt(&button);
	// Increment steady count until BUTTON_MAX_STEADY_COUNT is reached
	for(int i = 0; i < BUTTON_MAX_STEADY_COUNT; i++) {
		ButtonProcessInt(&button);
	}

	// Assert
	ASSERT_EQ(button.pressed, 0);
}
