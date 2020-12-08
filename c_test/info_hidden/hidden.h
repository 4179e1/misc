#ifndef _HIDDEN_H
#define _HIDDEN_H
typedef struct hidden Hidden;

Hidden *hidden_new (int a, int b);
int geta (Hidden *hide);
void seta (Hidden *hide, int value);
void hid_print (Hidden *hide);

#endif /* _HIDDEN_H */
