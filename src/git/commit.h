#ifndef YAGA_GIT_COMMIT_H
#define YAGA_GIT_COMMIT_H

#include <string>

#include <git2.h>

#include "oid.h"
#include "signature.h"

namespace yaga_git
{
    struct commit
    {
        static commit from_raw(git_commit* raw_commit);

        commit(
            const oid& commit_id,
            const std::string& message,
            const std::string& message_encoding,
            const std::string& summary,
            const time_with_offset& time,
            const signature& committer,
            const signature& author,
            const std::string& header,
            const oid& tree_id);

        const signature& author() const;
        const signature& committer() const;
        const oid& commit_id() const;
        const std::string& header() const;
        const std::string& message() const;
        const std::string& message_encoding() const;
        const std::string& summary() const;
        const time_with_offset time() const;
        const oid& tree_id() const;

      private:
        oid commit_id_;
        signature author_;
        signature committer_;
        std::string header_;
        std::string message_;
        std::string message_encoding_;
        std::string summary_;
        time_with_offset time_;
        oid tree_id_;

        commit(git_commit* raw_commit);
        static const char* get_safe_string(const char* str);
    };
}

#endif
