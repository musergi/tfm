# Dataset for CSCAs

This repository contains all the necessary components to record a dataset of a meltdown attacks. For the implementation
of the attack we relly in third parties in the `deps` folder.

## Running an example

With a regular pull of the reporitory the submodules are not downloaded for this reason we will first force the
submodules to be pulled.

```bash
git submodule init
git submodule update
```

After it we must build the example attacks:

```bash
cd deps/meltdown
make
```

We then need to build the monitoring software, for this step PAPI must be installed:

```bash
mkdir build
cd build
cmake ..
make
```

In order to run an execution we simply need to run the automated script (beware it uses python3):

```bash
python run_tests.py --vuln ./deps/meltdown/test --events PAPI_TOT_INS PAPI_L2_TCA PAPI_L2_TCM
python show_results.py --dataset out_labeled.csv
```

## Previous work

Many works have worked on the subject of detecting at Run-Time CSCAs however it is hard to compare the methodologies
used by different articles. The main reason is that most of them relly in their own datasets for the experiments.

The first of such articles is [Mushtaq et al.](https://hal.archives-ouvertes.fr/hal-01876792/document). It uses for the
creation of its dataset the PAPI library that provides access to 100+ events for Intel's core i7 family. The selected
events are the following:

| Hardware Event                | Feature ID |
| ----------------------------- | ---------- |
| L1 Data Cache Misses          | L1-DCM     |
| L1 Instruction Cache Misses   | L1-ICM     |
| L1 Total Cache Misses         | L1-TCM     |
| L2 Instruction Cache Accesses | L2-ICA     |
| L2 Instruction Cache Misses   | L2-ICM     |
| L2 Total Cache Accesses       | L2-TCA     |
| L2 Total Cache Misses         | L2-TCM     |
| L3 Instruction Cache Accesses | L3-ICA     |
| L3 Total Cache Accesses       | L3-TCA     |
| L3 Total Cache Misses         | L3-TCM     |
| Total CPU Cycles              | TOT-CYC    |
| Branch Miss Predictions       | BR-MSP     |

The tested attacks by this article are the Flush+Reload and Flush+Flush.

The second of such articles is [Chiappetta et al.](https://eprint.iacr.org/2015/1034.pdf). Hear the vulnerability is
explained in more detail pointing at the CLFLUSH instruction. This article does have a narrower scope than the previous
one. It only attempts to takle the attack of FLUSH+RELOAD. They build a custom tool using the PAPI library but do not
details the used features.

The third of such articles is [Depoix et al.](https://www.betriebssysteme.org/wp-content/uploads/2018/10/WAMOS_2018_paper_12.pdf).
In this article the authors also target the well tested FLUSH+RELOAD attack. They also use the PAPI library to record
Hardware performance counters.

| Hardware Event          | Feature ID |
| ----------------------- | ---------- |
| Total Instructions      | TOT-INS    |
| L3 Total Cache Accesses | L3-TCA     |
| L3 Total Cache Misses   | L3-TCM     |

## Work to do

As this previous works have shown we can clearly create a tool based on Machine Learning that is able to detect this
particular attacks. And there are plenty of them developped. However there is no unified metric between them as each of
them works with their particular dataset. From the previously seen articles the library to use is PAPI as it allows
to record numerous events with low lattency.

## Instalation

```bash
apt install papi-tools
```

## Goals

- [x] Install PAPI and run example
- [ ] Develop simple monitoring tool using PAPI
- [ ] Generate small proof of concept dataset
