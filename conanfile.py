import os

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class BKSysRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("asio/1.32.0")
        self.requires("mariadb-connector-c/3.4.3")
        self.requires("zlib/1.3.1")
        self.requires("fmt/11.0.2")
        self.requires("spdlog/1.15.0")
        self.requires("cpp-httplib/0.18.3")
        self.requires("openssl/3.3.2")
        self.requires("nlohmann_json/3.11.3")
        self.requires("imgui/1.91.5")
        self.requires("sdl/2.30.9")

    def generate(self):
        copy(self, "*sdl2*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        copy(self, "*sdlrenderer*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")
    def layout(self):
        cmake_layout(self)