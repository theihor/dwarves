#!/bin/bash

set -euxo pipefail

vmlinux=$1

# vmlinux=/home/theihor/git/kernel.org/bpf-next/kbuild-output/.tmp_vmlinux1

features=encode_force,var,float,enum64,decl_tag,type_tag,optimized_func,consistent_func,decl_tag_kfuncs

cmake -Bbuild -DCMAKE_BUILD_TYPE=Release && make -C build -j

for j in 3 6 12 24 48 96 192; do
    /usr/bin/time -f "-j${j} mem %M Kb, time %e sec" \
                  ./build/pahole -J -j$j \
                         --btf_features=$features \
                         --btf_encode_detached=/dev/null \
                         --lang_exclude=rust \
                         $vmlinux > /dev/null
done
