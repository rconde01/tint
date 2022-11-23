use_relative_paths = True

gclient_gn_args_file = 'build/config/gclient_args.gni'

gclient_gn_args = [
  'generate_location_tags',
]

vars = {
  'chromium_git': 'https://chromium.googlesource.com',

  'tint_gn_revision': 'git_revision:281ba2c91861b10fec7407c4b6172ec3d4661243',

  # We don't use location metadata in our test isolates.
  'generate_location_tags': False,
}

deps = {
  'third_party/gpuweb-cts': {
    'url': '{chromium_git}/external/github.com/gpuweb/cts@b0291fd966b55a5efc496772555b94842bde1085',
  },

  'third_party/vulkan-deps': {
    'url': '{chromium_git}/vulkan-deps@bd2c589d0d34612d9dd071396225d7de772c020c',
  },

  # Dependencies required to use GN/Clang in standalone
  'build': {
    'url': '{chromium_git}/chromium/src/build@01569374d46a14b225586c564146a8e1749520b6',
  },

  'buildtools': {
    'url': '{chromium_git}/chromium/src/buildtools@cccaf48c82bcf4ddafa6f8aa9f06014a1ef434bf',
  },

  'tools/clang': {
    'url': '{chromium_git}/chromium/src/tools/clang@a5e0d72349d028a4023927d6d166a8478355fac3',
  },

  'buildtools/clang_format/script': {
    'url': '{chromium_git}/external/github.com/llvm/llvm-project/clang/tools/clang-format.git@8b525d2747f2584fc35d8c7e612e66f377858df7',
  },

  'buildtools/linux64': {
    'packages': [{
      'package': 'gn/gn/linux-amd64',
      'version': Var('tint_gn_revision'),
    }],
    'dep_type': 'cipd',
    'condition': 'host_os == "linux"',
  },
  'buildtools/mac': {
    'packages': [{
      'package': 'gn/gn/mac-${{arch}}',
      'version': Var('tint_gn_revision'),
    }],
    'dep_type': 'cipd',
    'condition': 'host_os == "mac"',
  },
  'buildtools/win': {
    'packages': [{
      'package': 'gn/gn/windows-amd64',
      'version': Var('tint_gn_revision'),
    }],
    'dep_type': 'cipd',
    'condition': 'host_os == "win"',
  },

  'buildtools/third_party/libc++/trunk': {
    'url': '{chromium_git}/external/github.com/llvm/llvm-project/libcxx.git@26d0ab4151fd10c523fdbb5bbdb59aa5a5774820',
  },

  'buildtools/third_party/libc++abi/trunk': {
    'url': '{chromium_git}/external/github.com/llvm/llvm-project/libcxxabi.git@5c3e02e92ae8bbc1bf1001bd9ef0d76e044ddb86',
  },

  'third_party/ninja': {
    'packages': [
      # https://chrome-infra-packages.appspot.com/p/infra/3pp/tools/ninja
      {
        'package': 'infra/3pp/tools/ninja/${{platform}}',
        'version': 'version:2@1.8.2.chromium.3',
      }
    ],
    'dep_type': 'cipd',
  },

  # Dependencies required for testing
  'testing': {
    'url': '{chromium_git}/chromium/src/testing@e3e8c19554e8f47da85d35e4f990cdc30a061196',
  },

  'third_party/catapult': {
    'url': '{chromium_git}/catapult.git@4a0e6f034e9756605cfc837c8526588d6c13436b',
  },

  'third_party/benchmark': {
    'url': '{chromium_git}/external/github.com/google/benchmark.git@e991355c02b93fe17713efe04cbc2e278e00fdbd',
  },

  'third_party/googletest': {
    'url': '{chromium_git}/external/github.com/google/googletest.git@d1a0039b97291dd1dc14f123b906bb7622ffe07c',
  },

  'third_party/protobuf': {
    'url': '{chromium_git}/external/github.com/protocolbuffers/protobuf.git@fde7cf7358ec7cd69e8db9be4f1fa6a5c431386a',
  },
}

hooks = [
  # Pull clang-format binaries using checked-in hashes.
  {
    'name': 'clang_format_win',
    'pattern': '.',
    'condition': 'host_os == "win"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'buildtools/win/clang-format.exe.sha1',
    ],
  },
  {
    'name': 'clang_format_mac_x64',
    'pattern': '.',
    'condition': 'host_os == "mac" and host_cpu == "x64"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'buildtools/mac/clang-format.x64.sha1',
                '-o', 'buildtools/mac/clang-format',
    ],
  },
  {
    'name': 'clang_format_mac_arm64',
    'pattern': '.',
    'condition': 'host_os == "mac" and host_cpu == "arm64"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'buildtools/mac/clang-format.arm64.sha1',
                '-o', 'buildtools/mac/clang-format',
    ],
  },
  {
    'name': 'clang_format_linux',
    'pattern': '.',
    'condition': 'host_os == "linux"',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-clang-format',
                '-s', 'buildtools/linux64/clang-format.sha1',
    ],
  },

  # Pull the compilers and system libraries for hermetic builds
  {
    'name': 'sysroot_x86',
    'pattern': '.',
    'condition': 'checkout_linux and ((checkout_x86 or checkout_x64))',
    'action': ['python3', 'build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=x86'],
  },
  {
    'name': 'sysroot_x64',
    'pattern': '.',
    'condition': 'checkout_linux and (checkout_x64)',
    'action': ['python3', 'build/linux/sysroot_scripts/install-sysroot.py',
               '--arch=x64'],
  },
  {
    # Update the Mac toolchain if necessary.
    'name': 'mac_toolchain',
    'pattern': '.',
    'condition': 'checkout_mac',
    'action': ['python3', 'build/mac_toolchain.py'],
  },
  {
    # Update the Windows toolchain if necessary. Must run before 'clang' below.
    'name': 'win_toolchain',
    'pattern': '.',
    'condition': 'checkout_win',
    'action': ['python3', 'build/vs_toolchain.py', 'update', '--force'],
  },
  {
    # Note: On Win, this should run after win_toolchain, as it may use it.
    'name': 'clang',
    'pattern': '.',
    'action': ['python3', 'tools/clang/scripts/update.py'],
  },
  {
    # Pull rc binaries using checked-in hashes.
    'name': 'rc_win',
    'pattern': '.',
    'condition': 'checkout_win and (host_os == "win")',
    'action': [ 'download_from_google_storage',
                '--no_resume',
                '--no_auth',
                '--bucket', 'chromium-browser-clang/rc',
                '-s', 'build/toolchain/win/rc/win/rc.exe.sha1',
    ],
  },
  # Update build/util/LASTCHANGE.
  {
    'name': 'lastchange',
    'pattern': '.',
    'action': ['python3', 'build/util/lastchange.py',
               '-o', 'build/util/LASTCHANGE'],
  },
]

recursedeps = [
  # buildtools provides clang_format, libc++, and libc++abi
  'buildtools',
  # vulkan-deps provides spirv-headers, spirv-tools & gslang
  # It also provides other Vulkan tools that Tint doesn't use
  'third_party/vulkan-deps',
]
