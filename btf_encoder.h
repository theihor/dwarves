#ifndef _BTF_ENCODER_H_
#define _BTF_ENCODER_H_ 1
/*
  SPDX-License-Identifier: GPL-2.0-only

  Copyright (C) 2019 Facebook

  Derived from ctf_encoder.h, which is:
  Copyright (C) Arnaldo Carvalho de Melo <acme@redhat.com>
 */

#include <stdbool.h>

struct btf_encoder;
struct btf;
struct cu;
struct list_head;

struct btf_encoder *btf_encoder__new(struct cu *cu, const char *detached_filename, struct btf *base_btf, bool verbose, struct conf_load *conf_load);
void btf_encoder__delete(struct btf_encoder *encoder);

int btf_encoder__encode(struct btf_encoder *encoder);

int btf_encoder__encode_cu(struct btf_encoder *encoder, struct cu *cu, struct conf_load *conf_load);

struct btf *btf_encoder__btf(struct btf_encoder *encoder);

int btf_encoder__add_saved_funcs(struct btf_encoder *encoder);
int btf_encoder__merge_encoders(struct btf_encoder *base_encoder, struct btf_encoder **encoders, int nr_encoders);

int btf_encoder__pre_cus__load_module(struct process_dwflmod_parms *parms, Dwfl_Module *mod, Dwarf *dw, Elf *elf);

#endif /* _BTF_ENCODER_H_ */
