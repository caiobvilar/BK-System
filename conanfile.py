import os
from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy

class BKSysRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("spdlog/1.16.0")
        self.requires("openssl/3.6.0")
        self.requires("nlohmann_json/3.12.0")
        self.requires("imgui/1.92.4")
        self.requires("asio/1.28.0")
        self.requires("cpp-httplib/0.18.3")
        self.requires("zlib/1.3.1")
        self.requires("boost/1.89.0")
        # Use C++ connector instead of C connector
        # mariadb-connector-cpp requires the C connector as dependency
        # but we'll use system packages to avoid build issues
        # Note: SDL2 and MariaDB will be provided by system packages

    def system_requirements(self):
        # SDL2 and MariaDB from system packages
        pass

    def generate(self):
        try:
            copy(self, "*sdl2*", os.path.join(self.dependencies["imgui"].package_folder,
                "res", "bindings"), os.path.join(self.source_folder, "bindings"))
            copy(self, "*sdlrenderer*", os.path.join(self.dependencies["imgui"].package_folder,
                "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        except Exception as e:
            print(f"Warning: Could not copy SDL bindings: {e}")

    def build_requirements(self):
        self.tool_requires("cmake/4.1.2")

    def layout(self):
        cmake_layout(self)
