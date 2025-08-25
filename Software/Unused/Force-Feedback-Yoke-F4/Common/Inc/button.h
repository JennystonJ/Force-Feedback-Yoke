#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define BUTTON_MAX_STEADY_COUNT 10

typedef enum {
	BUTTON_STATE_IDLE,
	BUTTON_STATE_DEBOUNCING
} ButtonState_e;

typedef struct Button Button_t;

struct Button {
	int (*ButtonReadState)(Button_t *button);
	void (*ButtonStateChangedCallback)(Button_t *button);
	bool pressed;
	bool previouslyPressed;
	int steadyCount;
	ButtonState_e state;
};

void ButtonInit(Button_t *button, int (*ButtonReadState)(Button_t *button));
bool ButtonIsPressed(Button_t *button);
void ButtonProcessInt(Button_t *button);
void ButtonSetStateChangedCallback(Button_t *button,
		void (*ButtonStateChangedCallback)(Button_t *button));

#ifdef __cplusplus
}
#endif

#endif /* INC_BUTTON_H_ */
