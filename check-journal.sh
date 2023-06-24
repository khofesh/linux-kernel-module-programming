#!/bin/bash

sudo journalctl --since "1 hour ago" | grep kernel
