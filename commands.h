#ifndef INCLUDE_COMMANDS_H
#define INCLUDE_COMMANDS_H

void commands_execute(char* str);

void commands_dir(char* path);
void commands_cd(char* path);
void commands_echo(char* echo);

void commands_math(char* expression);
void commands_read(char* path);
void commands_edit(char* path);

#endif /* INCLUDE_COMMANDS_H */
