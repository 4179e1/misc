# /usr/bin/env python

import json


def sort_complex():
    items = [
        {
            "scope": {},
            "prio": 0,
        },
        {
            "scope": {'_svc': ['mysvc']},
            "prio": 10,
        },
        {
            "scope": {'_svc': ['mysvc'],
                      'k2': ['v2', 'v2.1', 'v2.2']},
            "prio": 10,
        },
        {
            "scope": {'_svc': ['mysvc'],
                      'k1': ['v1'],
                      'k2': ['k2.1'], },
            "prio": 10,
        },
        {
            "scope": {'_svc': 'mysvc',
                      'k3': ['v3.1']},
            "prio": 20,
        },
        {
            "scope": {'_svc': ['yoursvc']},
            "prio": 10,
        },
        {
            "scope": {'_svc': ['yoursvc'],
                      'k2': ['v2']},
            "prio": 10,
        },
        {
            "scope": {'_svc': 'yoursvc',
                      'k1': 'v1'},
            "prio": 10,
        }
    ]

    s = sorted(items, key=lambda i: i['scope'], reverse=True)
    s = sorted(s, key=lambda i: i['prio'], reverse=True)

    print(json.dumps(s, indent=2))


def sort_dict():
    ds = [
        {},
        {'_svc': 'mysvc'},
        {'_svc': 'mysvc',
         'k2': 'v2'},
        {'_svc': 'mysvc',
         'k1': 'v1'},
        {'_svc': 'yoursvc'},
        {'_svc': 'yoursvc',
         'k2': 'v2'},
        {'_svc': 'yoursvc',
         'k1': 'v1'},
    ]

    print(json.dumps(sorted(ds, reverse=True), indent=2))


if __name__ == '__main__':
    # sort_dict()
    sort_complex()
