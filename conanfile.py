from conan import ConanFile
from conan.tools.files import copy

class SetUp(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	generators = "CMakeToolchain", "CMakeDeps"

	def requirements(self):
		self.requires("raylib/5.0")
		
	def configure(self):
		pass

	def generate(self):
		pass