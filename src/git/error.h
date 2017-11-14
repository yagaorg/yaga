#ifndef YAGA_GIT_ERROR
#define YAGA_GIT_ERROR

#include <string>
#include <system_error>

#include <git2.h>

namespace yaga {
namespace git {

// Generic error codes returned by most libgit functions
enum class error_code {
    ok = GIT_OK,
    generic_error = GIT_ERROR,
    not_found = GIT_ENOTFOUND,
    exists = GIT_EEXISTS,
    ambigous = GIT_EAMBIGUOUS,
    buf_size = GIT_EBUFS,
    user = GIT_EUSER,
    bare_repo = GIT_EBAREREPO,
    unborn_branch = GIT_EUNBORNBRANCH,
    unmerged = GIT_EUNMERGED,
    non_fast_forward = GIT_ENONFASTFORWARD,
    invalid_spec = GIT_EINVALIDSPEC,
    conflict = GIT_ECONFLICT,
    locked = GIT_ELOCKED,
    modified = GIT_EMODIFIED,
    auth = GIT_EAUTH,
    certificate = GIT_ECERTIFICATE,
    applied = GIT_EAPPLIED,
    peel = GIT_EPEEL,
    eof = GIT_EEOF,
    invalid = GIT_EINVALID,
    uncommitted = GIT_EUNCOMMITTED,
    directory = GIT_EDIRECTORY
};

enum class error_category {
    none = GITERR_NONE,
    no_memory = GITERR_NOMEMORY,
    os = GITERR_OS,
    invalid = GITERR_INVALID,
    reference = GITERR_REFERENCE,
    zlib = GITERR_ZLIB,
    repository = GITERR_REPOSITORY,
    config = GITERR_CONFIG,
    regex = GITERR_REGEX,
    odb = GITERR_ODB,
    index = GITERR_INDEX,
    object = GITERR_OBJECT,
    net = GITERR_NET,
    tag = GITERR_TAG,
    tree = GITERR_TREE,
    indexer = GITERR_INDEXER,
    ssl = GITERR_SSL,
    submodule = GITERR_SUBMODULE,
    thread = GITERR_THREAD,
    stash = GITERR_STASH,
    checkout = GITERR_CHECKOUT,
    fetch_head = GITERR_FETCHHEAD,
    merge = GITERR_MERGE,
    ssh = GITERR_SSH,
    filter = GITERR_FILTER,
    revert = GITERR_REVERT,
    callback = GITERR_CALLBACK,
    cherry_pick = GITERR_CHERRYPICK,
    describe = GITERR_DESCRIBE,
    rebase = GITERR_REBASE,
    filesystem = GITERR_FILESYSTEM,
};

struct error {
    error() = default;
    static error from_last_error(int error_code);

    error_code code() const;
    const char* message() const;
    error_category category() const;

  private:
    constexpr error(int code, const git_error* raw_error);

    error_code original_code;
    const git_error* original_error = nullptr;
};

namespace detail {
struct error_code_category : public std::error_category {
    virtual const char* name() const noexcept override final;
    virtual std::string message(int c) const override final;
};
}  // namespace detail

// Make a global instance of our custom error category
const detail::error_code_category& git_error_code_category();

// A make_error_category global function that will be found by ADL
// for both the error code and its wrapper
std::error_code make_error_code(error_code e);
std::error_code make_error_code(error e);

}  // namespace git
}  // namespace yaga

// We need to register our custom error code as a std::error_code
namespace std {
template <>
struct is_error_code_enum<yaga::git::error_code> : true_type {};
}  // namespace std

#endif
