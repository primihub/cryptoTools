
release:
	#bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64  //:libcryptoTools --sandbox_debug
	#bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64 //:libcryptoTools
	#bazel build --cxxopt=-std=c++17 //:libcryptoTools
	bazel build --cxxopt=-std=c++17 //:frontend_cryptoTools
