#pragma once

const unsigned int COUNT_KEYS_PRESS = 6;

struct CommandPress {
  const String Key;
  const unsigned int Value;
} CommandMappingPress[COUNT_KEYS_PRESS] = {
  {"gui", KEY_LEFT_GUI},
  {"shift", KEY_LEFT_SHIFT},
  {"ctrl", KEY_LEFT_CTRL},
  {"alt", KEY_LEFT_ALT},
  {"del", KEY_DELETE},
  {"enter", KEY_RETURN}
};
