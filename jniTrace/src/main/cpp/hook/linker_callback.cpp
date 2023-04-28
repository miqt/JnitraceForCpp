//
// Created by zhenxi on 2022/1/21.
//
#include <iosfwd>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <jni.h>
#include <dlfcn.h>
#include <cstddef>
#include <fcntl.h>
#include <dirent.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sstream>
#include <ostream>

#include <cstdlib>
#include <sys/ptrace.h>
#include <sys/stat.h>
#include <syscall.h>
#include <climits>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <pthread.h>
#include <vector>
#include <zlib.h>
#include <list>
#include <string>
#include <map>
#include <list>

#include <cstring>
#include <cstdio>
#include <regex>
#include <cerrno>
#include <climits>
#include <iostream>
#include <fstream>

#include "linkerHandler.h"
#include "linker_callback.h"
#include "logging.h"
#include "libpath.h"
#include "HookUtils.h"
#include "appUtils.h"
#include "fileUtils.h"
#include "mylibc.h"
#include "elf_util.h"

#define MATCH_ELF "libil2cpp.so"


namespace linker_callback {
    static bool isSave = false;
    static std::ofstream *hookStrHandlerOs;
}
using namespace ZhenxiRunTime;
using namespace linker_callback;

class FunJniLinkerCallBack : public LinkerLoadCallBack {
public:
    void loadBefore(const char *path) const override {

    }

    void loadAfter(const char *path, const char *redirect_path, void *ret) const override {
        if (path == nullptr) {
            return;
        }
        if (isSave) {
            if (hookStrHandlerOs != nullptr) {
                (*hookStrHandlerOs) << path;
            }
        }
        LOG(INFO) << path;
    }
};


void linkerCallBack::hookLinkerCallBack(std::ofstream *os) {
    if (os != nullptr) {
        linker_callback::isSave = true;
        linker_callback::hookStrHandlerOs = os;
    }
    ZhenxiRunTime::linkerHandler::init();
    ZhenxiRunTime::linkerHandler::addLinkerCallBack(new FunJniLinkerCallBack());
}
