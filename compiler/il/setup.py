from setuptools import setup, find_packages

setup(
    name="ledil",
    version="0.1",
    packages=find_packages(),
    entry_points={
        "console_scripts": [
            "ledil = ledil.__main__:main"
        ]
    }
)
