#pragma once

const unsigned int COUNT_KEYS_PRESS = 35;

struct PressKeyboard {
  const String Key;
  const unsigned int Value;
} PressKeyboardMapping[COUNT_KEYS_PRESS] = {
  {"enter", KEY_RETURN},
  {"ctrl", KEY_LEFT_CTRL},
  {"shift", KEY_LEFT_SHIFT},
  {"alt", KEY_LEFT_ALT},
  {"gui", KEY_LEFT_GUI},
  {"up", KEY_UP_ARROW},
  {"uparrow", KEY_UP_ARROW},
  {"down", KEY_DOWN_ARROW},
  {"downarrow", KEY_DOWN_ARROW},
  {"left", KEY_LEFT_ARROW},
  {"leftarrow", KEY_LEFT_ARROW},
  {"right", KEY_RIGHT_ARROW},
  {"rightarrow", KEY_RIGHT_ARROW},
  {"backspace", KEY_BACKSPACE},
  {"tab", KEY_TAB},
  {"esc", KEY_ESC},
  {"insert", KEY_INSERT},
  {"delete", KEY_DELETE},
  {"pageup", KEY_PAGE_UP},
  {"pagedown", KEY_PAGE_DOWN},
  {"home", KEY_HOME},
  {"end", KEY_END},
  {"capslock", KEY_CAPS_LOCK},
  {"f1", KEY_F1},
  {"f2", KEY_F2},
  {"f3", KEY_F3},
  {"f4", KEY_F4},
  {"f5", KEY_F5},
  {"f6", KEY_F6},
  {"f7", KEY_F7},
  {"f8", KEY_F8},
  {"f9", KEY_F9},
  {"f10", KEY_F10},
  {"f11", KEY_F11},
  {"f12", KEY_F12}
};
