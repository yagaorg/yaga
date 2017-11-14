#ifndef YAGA_GIT_OID_H
#define YAGA_GIT_OID_H

#include <git2.h>
#include <gsl/gsl>

namespace yaga {
namespace git {

struct oid {
    explicit oid(gsl::cstring_span<> str);
    explicit oid(git_oid&& oid_raw);
    git_oid& raw();
    const git_oid& raw() const;

  private:
    git_oid oid_raw;
};

}  // namespace git
}  // namespace yaga

#endif
