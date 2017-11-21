#ifndef YAGA_GIT_COMMIT_H
#define YAGA_GIT_COMMIT_H

#include <functional>
#include <memory>

#include <git2.h>
#include <stx/string_view.hpp>

#include "oid.h"
#include "signature.h"

namespace yaga_git
{
    struct commit
    {
        commit(git_commit* raw_commit);

        const signature& author() const;
        const signature& committer() const;
        const oid& commit_id() const;
        const stx::string_view& header() const;
        const stx::string_view& message() const;
        const stx::string_view& message_encoding() const;
        const stx::string_view& summary() const;
        const time_with_offset time() const;
        const oid& tree_id() const;

      private:
        oid commit_id_;
        signature author_;
        signature committer_;
        stx::string_view header_;
        stx::string_view message_;
        stx::string_view message_encoding_;
        std::unique_ptr<git_commit, decltype(&git_commit_free)> raw_commit_;
        stx::string_view summary_;
        time_with_offset time_;
        oid tree_id_;

        const char* get_safe_string(const char* str);
    };
}

#endif
