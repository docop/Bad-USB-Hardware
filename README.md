Bad-USB-Hardware
=====

A Bluetooth-controlled BadUSB device to remotely trigger payload with a keyboard press sequence.

A device pretending to be an HID interface. Works like a keyboard and lets you execute individual script commands.

ATmega32u4 + Bluetooth HC-05 components were used to build the device.

![Sketch](https://raw.github.com/mserafin/Bad-USB-Hardware/master/sketch.png){ width=50% }

> I don't take any responsibility for what you do with this project.

# Syntax

## Commands not using the keyboard.

| Command      | Example                       | Description 
|--------------|-------------------------------|--------------------------
| rem          | `<REM My First Payload>`      | Comment.
| string       | `<STRING notepad.exe>`        | Processes the text.
| delay        | `<DELAY 100>`                 | Creates a momentary pause.
| delaydefault | `<DELAYDEFAULT 100>`          | Used to change the pause between commands. The default is 10 milliseconds.
| repeat       | `<REPEAT 5>`                  | Repeats commands between `REPEAT` and` REPEATEND` n times. Default 1 times.
| repeatend    | `<REPEATEND>`                 | --//--


## Keyboard mapping commands.

| Command    | Example         | Key         
|------------|-----------------|-------------
| enter      | `<ENTER>`       | ENTER
| ctrl       | `<CTRL>`        | LEFT CTRL
| shift      | `<SHIFT>`       | LEFT SHIFT
| alt        | `<ALT>`         | LEFT ALT
| gui        | `<GUI r>`       | LEFT GUI
| up         | `<UP>`          | UP ARROW
| uparrow    | `<UPARROW>`     | UP ARROW
| down       | `<DOWN>`        | DOWN ARROW
| downarrow  | `<DOWNARROW>`   | DOWN ARROW
| left       | `<LEFT>`        | LEFT ARROW
| leftarrow  | `<LEFTARROW>`   | LEFT ARROW
| right      | `<RIGHT>`       | RIGHT ARROW
| rightarrow | `<RIGHT ARROW>` | RIGHT ARROW
| backspace  | `<BACKSPACE>`   | BACKSPACE
| tab        | `<TAB>`         | TAB
| esc        | `<ESC>`         | ESC
| insert     | `<INSERT>`      | INSERT
| delete     | `<DELETE>`      | DELETE
| pageup     | `<PAGEUP>`      | PAGE UP
| pagedown   | `<PAGEDOWN>`    | PAGE DOWN
| home       | `<HOME>`        | HOME
| end        | `<END>`         | END
| capslock   | `<CAPSLOCK>`    | CAPS LOCK
| f1         | `<F1>`          | F1
| f2         | `<F2>`          | F2
| f3         | `<F3>`          | F3
| f4         | `<F4>`          | F4
| f5         | `<F5>`          | F5
| f6         | `<F6>`          | F6
| f7         | `<F7>`          | F7
| f8         | `<F8>`          | F8
| f9         | `<F9>`          | F9
| f10        | `<F10>`         | F10
| f11        | `<F11>`         | F11
| f12        | `<F12>`         | F12

# Example

```xml
<REM My First Payload>
<GUI d>
<DELAY 100>
<GUI r>
<DELAY 100>
<STRING notepad.exe>
<ENTER>
<DELAY 100>
<REPEAT 10>
    <STRING Hello world>
    <ENTER>
<REPEATEND>
```

## Many keys in one command
```xml
<CTRL ALT DELETE>
```

```xml
<GUI r>
```

## Repeating commands 5 times.
```xml
<REPEAT 5>
  <DOWN>
  <RIGHT>
<REPEATEND>
```

# License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details