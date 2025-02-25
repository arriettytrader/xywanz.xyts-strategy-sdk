#pragma once

#include <algorithm>
#include <functional>
#include <span>
#include <string>
#include <tuple>
#include <vector>

namespace xyu {

inline std::vector<std::string_view> SplitString(std::string_view str, std::string_view delim,
                                                 bool skip_empty_elem = true) {
  std::vector<std::string_view> results;
  std::size_t start = 0, end;
  while ((end = str.find(delim, start)) != std::string::npos) {
    auto size = end - start;
    if (size != 0) {
      results.emplace_back(str.cbegin() + start, size);
    } else if (!skip_empty_elem) {
      results.emplace_back("");
    }
    start = end + delim.size();
  }

  if (start != str.size()) {
    results.emplace_back(str.cbegin() + start, str.size() - start);
  } else if (!skip_empty_elem) {
    results.emplace_back("");
  }
  return results;
}

inline std::vector<std::string_view> SplitLines(std::string_view str, bool keepends = false) {
  std::vector<std::string_view> lines;
  std::size_t start = 0, end;
  while ((end = str.find('\n', start)) != std::string::npos) {
    auto size = end - start;
    if (keepends) {
      size += 1;
    }
    lines.emplace_back(str.cbegin() + start, size);
    start = end + 1;
  }

  if (start != str.size()) {
    lines.emplace_back(str.cbegin() + start, str.size() - start);
  }
  return lines;
}

inline std::string ReplaceString(std::string_view str, std::string_view from, std::string_view to) {
  std::string ret(str);
  if (from.empty()) {
    return ret;
  }
  std::size_t pos = 0;
  while ((pos = ret.find(from, pos)) != std::string::npos) {
    ret.replace(pos, from.size(), to);
    pos += to.size();
  }
  return ret;
}

template <class ToTrim>
inline std::string_view LTrim(std::string_view sv, ToTrim to_trim) {
  while (!sv.empty() && to_trim(sv.front())) {
    sv.remove_prefix(1);
  }
  return sv;
}

template <class ToTrim>
inline std::string_view RTrim(std::string_view sv, ToTrim to_trim) {
  while (!sv.empty() && to_trim(sv.back())) {
    sv.remove_suffix(1);
  }
  return sv;
}

template <class ToTrim>
inline std::string_view Trim(std::string_view sv, ToTrim to_trim) {
  return LTrim(RTrim(sv, std::ref(to_trim)), std::ref(to_trim));
}

inline bool IsOddSpace(char c) { return c == '\n' || c == '\t' || c == '\r'; }

inline std::string_view LTrimWhiteSpace(std::string_view sv) {
  for (;;) {
    while (!sv.empty() && sv.front() == ' ') {
      sv.remove_prefix(1);
    }
    if (!sv.empty() && IsOddSpace(sv.front())) {
      sv.remove_prefix(1);
      continue;
    }

    return sv;
  }
}

inline std::string_view RTrimWhiteSpace(std::string_view sv) {
  for (;;) {
    while (!sv.empty() && sv.back() == ' ') {
      sv.remove_suffix(1);
    }
    if (!sv.empty() && IsOddSpace(sv.back())) {
      sv.remove_suffix(1);
      continue;
    }

    return sv;
  }
}

inline std::string_view TrimWhiteSpace(std::string_view sv) {
  return LTrimWhiteSpace(RTrimWhiteSpace(sv));
}

inline std::string UpperCase(std::string_view sv) {
  std::string ret(sv);
  std::transform(ret.cbegin(), ret.cend(), ret.begin(), [](char c) {
    if ('a' <= c && c <= 'z') {
      c += ('A' - 'a');
    }
    return c;
  });
  return ret;
}

inline std::string LowerCase(std::string_view sv) {
  std::string ret(sv);
  std::transform(ret.cbegin(), ret.cend(), ret.begin(), [](char c) {
    if ('A' <= c && c <= 'Z') {
      c -= ('A' - 'a');
    }
    return c;
  });
  return ret;
}

}  // namespace xyu
