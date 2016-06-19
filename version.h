#define VER_MAJOR    0
#define VER_MINOR    1
#define VER_REVISION 0
#define VER_BUILD    0

// macro
#define _BUILD_VERSION_(major,minor,revision,build) #major "." #minor "." #revision "." #build "\0"
#define BUILD_VERSION(major, minor, revision, build) _BUILD_VERSION_(major, minor, revision, build)

// for rc
#define VER_STRING BUILD_VERSION(VER_MAJOR, VER_MINOR, VER_REVISION, VER_BUILD)

