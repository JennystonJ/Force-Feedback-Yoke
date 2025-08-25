#include "button.h"
#include <stddef.h>

void ButtonInit(Button_t *button, int (*ButtonReadState)(Button_t *button)) {

	button->ButtonReadState = ButtonReadState;
	button->ButtonStateChangedCallback = NULL;

	button->state = BUTTON_STATE_IDLE;
	button->pressed = false;
	button->previouslyPressed = button->pressed;
	button->steadyCount = 0;


}

bool ButtonIsPressed(Button_t *button) {
	return button->pressed;
}

void ButtonProcessInt(Button_t *button) {

	// Read current state of button and check if there's a change
	bool readingPressed = button->ButtonReadState(button) == 1;
	bool changedState = readingPressed != button->previouslyPressed;

	if(button->state == BUTTON_STATE_IDLE && changedState) {

		button->state = BUTTON_STATE_DEBOUNCING;
	}
	else if(button->state == BUTTON_STATE_DEBOUNCING) {

		if(changedState) {
			// Button is unsteady, reset counter
			button->steadyCount = 0;
		}
		else {
			button->steadyCount++;

			// Check if button has remained in the same state for
			// max steady count duration
			if(button->steadyCount >= BUTTON_MAX_STEADY_COUNT) {
				// Reset counter and update button state
				button->steadyCount = 0;
				button->pressed = readingPressed;
				button->state = BUTTON_STATE_IDLE;

				// Perform callback for button state changed if available
				if(button->ButtonStateChangedCallback != NULL) {
					button->ButtonStateChangedCallback(button);
				}
			}
		}
	}
	else {

		// If the button state is neither idle nor debouncing,
		// set to idle (code should not reach here)
		button->state = BUTTON_STATE_IDLE;
	}

	// Update previous state for next iteration
	button->previouslyPressed = readingPressed;
}

void ButtonSetStateChangedCallback(Button_t *button,
		void (*ButtonStateChangedCallback)(Button_t *button)) {
	button->ButtonStateChangedCallback = ButtonStateChangedCallback;
}
