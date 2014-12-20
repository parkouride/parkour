import sys
import os.path
import argparse
import jinja2
import json

OUTPUT_FORMATS = [
    'py', 'cpp'
]


def setup_template_environment(subdir):
    return jinja2.Environment(
        loader=jinja2.PackageLoader('gen', 'templates/{}'.format(subdir))
    )

def generate_file(args, env, data, format_):
    template_name = "{}/file.txt".format(format_)
    template = env.get_template(template_name)

    output_filename = os.path.join(
        args.output_path,
        "{}.{}".format(
            os.path.splitext(os.path.basename(args.input_path))[0], format_
        )
    )
    with open(output_filename, "w") as f:
        page = template.render(data=data)
        print(page)

def generate_enum(args):
    env = setup_template_environment("enum")
    data = json.load(open(args.input_path))
    for format_ in OUTPUT_FORMATS:
        generate_file(args, env, data, format_)


GENERATORS = {
    'enum': generate_enum,
}


def usage(args):
    parser = argparse.ArgumentParser()

    parser.add_argument('input_path')
    parser.add_argument('generator', choices=GENERATORS.keys())
    parser.add_argument('output_path')

    return parser.parse_args(args)


def main(args=sys.argv[1:]):
    args = usage(args)
    func = GENERATORS[args.generator]

    func(args)

if __name__ == "__main__":
    sys.exit(main())
