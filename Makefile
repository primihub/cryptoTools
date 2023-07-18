
release:
	#bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64	//:libcryptoTools --sandbox_debug
	#bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64 //:libcryptoTools
	#bazel build --cxxopt=-std=c++17 //:libcryptoTools
	#bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64 //:frontend_cryptoTools
	bazel build --cxxopt=-std=c++17 --define cpu_arch=x86_64 //:frontend_cryptoTools

.PHONY: clean

clean:
	bazel clean
