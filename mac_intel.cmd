#!/bin/bash

#SBATCH -o /home/hpc/pr63so/ga59how2/output_slurm/nhsw.%j.out
#SBATCH -D /home/hpc/pr63so/ga59how2/codes/nhsw/
#SBATCH -J nhsw
#SBATCH --get-user-env
#SBATCH --partition=snb
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1
# #SBATCH --export=NONE
#SBATCH --time=00:05:00

source /etc/profile.d/modules.sh

module load gcc

# mpiexec.hydra -genv OMP_NUM_THREADS 2 -ppn 8 -n 16 deviceQuery
./nhsw 10 10 10 3.5 0.1 10.0 10.0 10.0
