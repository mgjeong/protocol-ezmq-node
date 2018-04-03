{
  "targets": [
    {
      "target_name": "ezmq",
      "sources":["./src/ezmq.cc", "./src/nezmqapi.cc", "./src/nezmqreading.cc", "./src/nezmqevent.cc", "./src/nezmqpublisher.cc", "./src/nezmqbytedata.cc", "./src/nezmqsubscriber.cc"],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        './dependencies/protocol-ezmq-cpp/include/',
        './dependencies/protocol-ezmq-cpp/extlibs/zmq/',
        './dependencies/protocol-ezmq-cpp/protobuf/', 
      ],
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions', '-fno-rtti'],
      "cflags_cc": [ "-std=c++11" ],
      'conditions': [
          ['config=="x86_64_release"',
            {          
              "ldflags": [
              "-L<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86_64/release/",
              "-Wl,-rpath,<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86_64/release/",
              ]
            }
          ],
          ['config=="x86_64_debug"',
              {
                "ldflags": [
                "-L<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86_64/debug/",
                "-Wl,-rpath,<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86_64/debug/",
                ]
              }
          ],
          ['config=="x86_release"',
            {
              "ldflags": [
              "-L<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86/release/",
              "-Wl,-rpath,<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86/release/",
              ]
            }
          ],
          ['config=="x86_debug"',
              {
                "ldflags": [
                "-L<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86/debug/",
                "-Wl,-rpath,<(module_root_dir)/dependencies/protocol-ezmq-cpp/out/linux/x86/debug/",
                ]
              }
          ],
       ], 
      "libraries": [
          "-lezmq"
       ],

    }
  ]
}

