#include "commit.h"

using namespace std;

namespace yaga_git
{
    commit commit::from_raw(git_commit* raw_commit)
    {
        auto *commit_oid = git_commit_id(raw_commit);
        auto commit_id = oid(*commit_oid);

        auto message = get_safe_string(git_commit_message(raw_commit));
        auto message_encoding = get_safe_string(git_commit_message_encoding(raw_commit));
        auto summary = get_safe_string(git_commit_summary(raw_commit));

        auto raw_time = git_commit_time(raw_commit);
        auto raw_time_offset_min = git_commit_time_offset(raw_commit);
        auto time = time_with_offset(raw_time, raw_time_offset_min);

        auto committer = signature::from_raw(git_commit_committer(raw_commit));
        auto author = signature::from_raw(git_commit_author(raw_commit));

        auto header = get_safe_string(git_commit_raw_header(raw_commit));

        auto *tree_oid = git_commit_tree_id(raw_commit);
        auto tree_id = oid(*tree_oid);

        return commit(commit_id, message, message_encoding, summary, time, committer, author, header, tree_id);
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
          message_(message),
          message_encoding_(message_encoding),
          summary_(summary),
          time_(time),
          committer_(committer),
          author_(author),
          header_(header),
          tree_id_(tree_id)
    {}

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

    string commit::get_safe_string(const char *str)
    {
        return str == NULL ? string() : string(str);
    }
}
