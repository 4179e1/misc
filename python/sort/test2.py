items = [
    {
        "value": 100,
        "lk": [
            'k1',
            'k2',
            'k3',
        ],
        "lv":[
            ['v1.1', 'v1.2', 'v.13'],
        ],
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
