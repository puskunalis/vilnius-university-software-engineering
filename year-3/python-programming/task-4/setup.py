from distutils.core import setup, Extension

module = Extension('palindrome_module', sources=['palindrome_module.c'])

setup(name='PalindromeModule',
      version='1.0',
      description='Check if a given string is a palindrome',
      ext_modules=[module])
