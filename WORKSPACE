workspace(name = "cryptoTools")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

http_archive(
    name = "rules_foreign_cc",
    sha256 = "484fc0e14856b9f7434072bc2662488b3fe84d7798a5b7c92a1feb1a0fa8d088",
    strip_prefix = "rules_foreign_cc-0.8.0",
    #url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.8.0.tar.gz",
    url = "https://primihub.oss-cn-beijing.aliyuncs.com/tools/rules_foreign_cc_cn-0.8.0.tar.gz",
)
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")
rules_foreign_cc_dependencies()

git_repository(
  name = "com_github_nelhage_rules_boost",
  commit = "81945736a62fa8490d2ab6bb31705bb04ce4bb6c",
  #branch = "master",
  remote = "https://gitee.com/primihub/rules_boost.git",
  # shallow_since = "1591047380 -0700",
)
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

http_archive(
  name = "bazel_common",
  url = "https://primihub.oss-cn-beijing.aliyuncs.com/tools/bazel-common-master.zip",
  strip_prefix = "bazel-common-master",
  sha256 = "7034b3fb6b3051d70f33853fff48b0e931b57e35c6a32bba0280c6f2b6d6ee0c",
)

http_archive(
  name = "bazel_skylib",
  strip_prefix = None,
  url = "https://primihub.oss-cn-beijing.aliyuncs.com/tools/bazel-skylib-1.0.2.tar.gz",
  sha256 = "97e70364e9249702246c0e9444bccdc4b847bed1eb03c5a3ece4f83dfe6abc44",
)

load("@bazel_skylib//lib:versions.bzl", "versions")
versions.check(minimum_bazel_version = "5.0.0")


new_git_repository(
  name = "toolkit_relic",
  build_file = "//bazel:BUILD.relic",
  remote = "https://gitee.com/orzmzp/relic.git",
  commit = "3f616ad64c3e63039277b8c90915607b6a2c504c",
  shallow_since = "1581106153 -0800",
)

