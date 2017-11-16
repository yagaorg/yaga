#include "error.h"

#include <git2.h>

namespace yaga {
namespace git {

error error::from_last_error(int code) {
    return error(code, giterr_last());
}

error_code error::code() const {
    return original_code;
}

const char* error::message() const {
    return original_error ? original_error->message : "";
}

error_category error::category() const {
    return original_error ? static_cast<error_category>(original_error->klass)
                          : error_category::none;
}

constexpr error::error(int code, const git_error* raw_error)
    : original_code(static_cast<error_code>(code)), original_error(raw_error) {}

namespace detail {
const char* error_code_category::name() const noexcept {
    return "git error";
}

std::string error_code_category::message(int c) const {
    switch (static_cast<yaga::git::error_code>(c)) {
        case error_code::ok:
            return "Success";
        case error_code::generic_error:
            return "Generic error";
        case error_code::not_found:
            return "Requested object could not be found";
        case error_code::exists:
            return "Object exists preventing operation";
        case error_code::ambigous:
            return "More than one object matches";
        case error_code::buf_size:
            return "Output buffer too short to hold data";
        case error_code::user:
            return "User-generated error";
        case error_code::bare_repo:
            return "Operation not allowed on bare repository";
        case error_code::unborn_branch:
            return "HEAD refers to branch with no commits";
        case error_code::unmerged:
            return "Merge in progress prevented operation";
        case error_code::non_fast_forward:
            return "Reference was not fast-forwardable";
        case error_code::invalid_spec:
            return "Name/ref spec was not in a valid format";
        case error_code::conflict:
            return "Checkout conflicts prevented operation";
        case error_code::locked:
            return "Lock file prevented operation";
        case error_code::modified:
            return "Reference value does not match expected";
        case error_code::auth:
            return "Authentication error";
        case error_code::certificate:
            return "Server certificate is invalid";
        case error_code::applied:
            return "Patch/merge has already been applied";
        case error_code::peel:
            return "The requested peel operation is not possible";
        case error_code::eof:
            return "Unexpected EOF";
        case error_code::invalid:
            return "Invalid operation or input";
        case error_code::uncommitted:
            return "Uncommitted changes in index prevented operation";
        case error_code::directory:
            return "Operation was not valid for a directory,";
        default:
            return "Unknown error";
    }
}
}  // namespace detail

const detail::error_code_category& git_error_code_category() {
    static detail::error_code_category c;
    return c;
}

std::error_code make_error_code(error_code e) {
    return {static_cast<int>(e), git_error_code_category()};
}

std::error_code make_error_code(error e) {
    return make_error_code(e.code());
}

}  // namespace git
}  // namespace yaga
