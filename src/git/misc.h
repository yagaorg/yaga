#pragma once

#include <git2.h>

#include "repository.h"

namespace yaga {
namespace git {

struct libgit {
  libgit() {
    git_libgit2_init();
  }

  ~libgit() {
    git_libgit2_shutdown();
  }
};

inline void init() {
  static libgit git;
}

}
}
