from setuptools import setup, find_packages

setup(
    name='codegen',
    version='0.1',
    entry_points={
        'console_scripts': [
            'codegen = gen:main'
        ]
    },
    requires=[
        "jinja2"
    ]
)
