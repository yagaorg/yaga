#include "checkout.h"

#include <type_traits>

namespace yaga {
namespace git {

checkout_progress_status::checkout_progress_status(const char* raw_path,
                                                   std::size_t completed,
                                                   std::size_t total)
    : path(raw_path), completed_steps(completed), total_steps(total) {}

checkout_notify_status::checkout_notify_status(git_checkout_notify_t why_raw,
                                               const char* path_raw,
                                               const git_diff_file* baseline_raw,
                                               const git_diff_file* target_raw,
                                               const git_diff_file* workdir_raw)
    : why(static_cast<checkout_notification_type>(why_raw)),
      path(path_raw),
      baseline(baseline_raw),
      target(target_raw),
      workdir(workdir_raw) {}

checkout_options& checkout_options::strategy(checkout_strategy strategy) {
    strategy_ = strategy;
    return *this;
}

checkout_options& checkout_options::disable_filters(bool disable) {
    disable_filters_ = disable;
    return *this;
}

checkout_options& checkout_options::directory_mode(unsigned int mode) {
    dir_mode_ = mode;
    return *this;
}

checkout_options& checkout_options::file_mode(unsigned int mode) {
    file_mode_ = mode;
    return *this;
}

checkout_options& checkout_options::notifcation_types(checkout_notification_type types) {
    notify_flags_ = types;
    return *this;
}

checkout_options& checkout_options::paths(const std::vector<char*>& paths) {
    paths_ = paths;
    return *this;
}

checkout_options& checkout_options::target_directory(const std::string& directory) {
    target_directory_ = directory;
    return *this;
}

checkout_options& checkout_options::ancestor_label(const std::string& label) {
    ancestor_label_ = label;
    return *this;
}

checkout_options& checkout_options::our_label(const std::string& label) {
    our_label_ = label;
    return *this;
}

checkout_options& checkout_options::their_label(const std::string& label) {
    their_label_ = label;
    return *this;
}

git_checkout_options checkout_options::build() {
    git_checkout_options options = GIT_CHECKOUT_OPTIONS_INIT;
    if (strategy_) {
        options.checkout_strategy = static_cast<git_checkout_strategy_t>(strategy_.value());
    }

    if (disable_filters_) {
        options.disable_filters = disable_filters_.value();
    }

    if (dir_mode_) {
        options.dir_mode = dir_mode_.value();
    }

    if (file_mode_) {
        options.file_mode = file_mode_.value();
    }

    if (notify_flags_) {
        options.notify_flags = static_cast<git_checkout_notify_t>(notify_flags_.value());
    }

    if (paths_) {
        options.paths.strings = paths_.value().data();
    }

    if (target_directory_) {
        options.target_directory = target_directory_.value().data();
    }

    if (ancestor_label_) {
        options.ancestor_label = ancestor_label_.value().data();
    }

    if (our_label_) {
        options.ancestor_label = ancestor_label_.value().data();
    }

    if (their_label_) {
        options.ancestor_label = ancestor_label_.value().data();
    }

    if (progress_callback_) {
        // We send the original callback in place of the payload. C++ lambdas provide a
        // more natural way for capturing values in the enclosing scope then passing
        // a separate payload
        options.progress_cb = [](const char* path, std::size_t completed_steps,
                                 std::size_t total_steps, void* cb) {
            const auto* original = reinterpret_cast<checkout_progress_callback*>(cb);
            (*original)(checkout_progress_status(path, completed_steps, total_steps));
        };
        options.progress_payload = &progress_callback_.value();
    }

    if (notify_callback_) {
        options.notify_cb = [](git_checkout_notify_t why, const char* path,
                               const git_diff_file* baseline, const git_diff_file* target,
                               const git_diff_file* workdir, void* cb) {
            const auto* original = reinterpret_cast<checkout_notify_callback*>(cb);
            return (*original)(checkout_notify_status(why, path, baseline, target, workdir));
        };
        options.notify_payload = &notify_callback_.value();
    }

    return options;
}

checkout_strategy operator|(checkout_strategy a, checkout_strategy b) {
    using int_type = std::underlying_type<checkout_strategy>::type;
    return static_cast<checkout_strategy>(static_cast<int_type>(a) | static_cast<int_type>(b));
}

checkout_strategy operator&(checkout_strategy a, checkout_strategy b) {
    using int_type = std::underlying_type<checkout_strategy>::type;
    return static_cast<checkout_strategy>(static_cast<int_type>(a) & static_cast<int_type>(b));
}

checkout_notification_type operator|(checkout_notification_type a, checkout_notification_type b) {
    using int_type = std::underlying_type<checkout_notification_type>::type;
    return static_cast<checkout_notification_type>(static_cast<int_type>(a) |
                                                   static_cast<int_type>(b));
}

checkout_notification_type operator&(checkout_notification_type a, checkout_notification_type b) {
    using int_type = std::underlying_type<checkout_notification_type>::type;
    return static_cast<checkout_notification_type>(static_cast<int_type>(a) &
                                                   static_cast<int_type>(b));
}

}  // namespace git
}  // namespace yaga
