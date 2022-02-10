# Dataset for CSCAs

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
