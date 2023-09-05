#ifdef __cplusplus
extern "C" {
#endif

void _prolog();
void _epilog();
void _unresolved();

typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

extern void ModuleProlog(void);
extern void ModuleEpilog(void);
extern void ModuleUnresolved(void);
extern void ModuleConstructorsX(const VoidFunc* ctors);
extern void ModuleDestructorsX(const VoidFunc* dtors);

#ifdef __cplusplus
}
#endif

void _prolog(void) {
    ModuleConstructorsX(_ctors);
    ModuleProlog();
}

void _epilog(void) {
    ModuleEpilog();
    ModuleDestructorsX(_dtors);
}

void _unresolved(void) {
    ModuleUnresolved();
}
