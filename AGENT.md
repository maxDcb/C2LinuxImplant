# AGENT.md - C2LinuxImplant

## CI/CD Contract

- CI runs on `pull_request` and every branch push, including tag pushes before release publication.
- CD publishes only from tag builds after the CI build, tests, deliverable validation, and archive staging have succeeded.
- GitHub Actions permissions stay read-only by default. Only the release publication job may request `contents: write`.

## Build and Test Contract

- Linux CI builds with Conan through `conan_provider.cmake`.
- The CI configure step must pass `-DC2CORE_BUILD_TESTS=ON`.
- Tests must be visible from the top-level build directory and run with `ctest --test-dir <build-dir> --output-on-failure --timeout 60`.
- Do not silently skip unstable tests. Fix them when reasonable, or isolate them explicitly with a documented reason.
- `libs/libDns/tests/fonctionalTest` is intentionally not registered in CI because it is a manual server/client harness and exits with usage information unless runtime arguments are provided.

## Release Layout

C2TeamServer consumes Linux release payloads from the archive layout below:

```text
Release/
  LinuxBeacons/
    BeaconDns
    BeaconGithub
    BeaconHttp
    BeaconSmb
    BeaconTcp
  LinuxModules/
    lib*.so
```

The CMake build may copy intermediate deliverables into `Release/Beacons` and `Release/Modules`, but packaging must not rename, delete, or mutate those source output directories. Stage archives from a clean `artifacts/Release` tree instead.
