# Copyright (c) 2014, Im Kyeong-Hyeon
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from conans import ConanFile, CMake
import os, re

class Project(ConanFile):
    name = 'ikh-widget-library'
    version = '1.0.0'
    url = 'https://github.com/dlarudgus20/ikh-widget-library.git'
    license = 'BSD-2-Clause'
    author = 'Im Kyeong-Hyeon (dlarudgus20@naver.com)'

    settings = 'os', 'compiler', 'build_type', 'arch'
    requires = \
        'Boost/1.60.0@lasote/stable', \
        'glew/1.13.0@coding3d/ci', \
        'glm/0.9.7.6@dlarudgus20/stable'
    generators = 'cmake'

    def source(self):
        self.run('git clone ' + Project.url)

    def build(self):
        cmake = CMake(self.settings)
        self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy('*.hpp', dst='include', src='libiwl')
        if self.settings.os == 'Windows':
            if self.options.shared:
                self.copy('*.dll', dst='bin', keep_path=False)
                self.copy('*.lib', dst='lib', keep_path=False)
            else:
                self.copy('*.lib', dst='lib', keep_path=False)
        else:
            if self.options.shared:
                if self.settings.os == 'Macos':
                    self.copy('*.dylib', dst='lib', keep_path=False)
                else:
                    self.copy('*.so', dst='lib', keep_path=False)
            else:
                self.copy('*.a', dst='lib', keep_path=False)

    def package_info(self):
        if self.settings.os == 'Windows':
            self.cpp_info.libs = [ 'libiwl' ]
        else:
            self.cpp_info.libs = [ 'iwl' ]
