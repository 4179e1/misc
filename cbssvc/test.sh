#!/bin/bash - 
curl -X POST -H "Content-Type: application/json"  -d @example-preset.json http://localhost:5000/api/v1/presets
