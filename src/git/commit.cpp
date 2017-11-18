#include "commit.h"

using namespace std;

namespace yaga_git
{
    commit commit::from_raw(git_commit* raw_commit)
    {
        return commit(raw_commit);
    }

    commit::commit(
        const oid& commit_id,
        const string& message,
        const string& message_encoding,
        const string& summary,
        const time_with_offset& time,
        const signature& committer,
        const signature& author,
        const string& header,
        const oid& tree_id)
        : commit_id_(commit_id),
          author_(author),
          committer_(committer),
          header_(header),
          message_(message),
          message_encoding_(message_encoding),
          summary_(summary),
          time_(time),
          tree_id_(tree_id)
    {
    }

    commit::commit(git_commit* raw_commit)
        : commit_id_(*git_commit_id(raw_commit)),
          author_(git_commit_author(raw_commit)),
          committer_(git_commit_committer(raw_commit)),
          header_(get_safe_string(git_commit_raw_header(raw_commit))),
          message_(get_safe_string(git_commit_message(raw_commit))),
          message_encoding_(get_safe_string(git_commit_message_encoding(raw_commit))),
          summary_(get_safe_string(git_commit_summary(raw_commit))),
          time_(git_commit_time(raw_commit), git_commit_time_offset(raw_commit)),
          tree_id_(*git_commit_tree_id(raw_commit))
    {
    }

    const signature& commit::author() const
    {
        return author_;
    }

    const signature& commit::committer() const
    {
        return committer_;
    }

    const oid& commit::commit_id() const
    {
        return commit_id_;
    }

    const string& commit::header() const
    {
        return header_;
    }

    const string& commit::message() const
    {
        return message_;
    }

    const string& commit::message_encoding() const
    {
        return message_encoding_;
    }

    const string& commit::summary() const
    {
        return summary_;
    }

    const time_with_offset commit::time() const
    {
        return time_;
    }

    const oid& commit::tree_id() const
    {
        return tree_id_;
    }

    const char* commit::get_safe_string(const char* str)
    {
        return str == NULL ? "" : str;
    }
}
