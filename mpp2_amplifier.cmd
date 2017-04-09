#!/bin/bash
#SBATCH -o /home/hpc/pr63so/ga59how2/codes/NHSW/myjob.%j.%N.out
#SBATCH -D /home/hpc/pr63so/ga59how2/codes/NHSW
#SBATCH -J PARA
#SBATCH --get-user-env
#SBATCH --clusters=mpp2

#SBATCH --nodes=1
#SBATCH --tasks-per-node=28

#SBATCH --time=01:00:00
source /etc/profile.d/modules.sh
cd /home/hpc/pr63so/ga59how2/codes/NHSW/

module load advisor_xe
module load inspector_xe
module load amplifier_xe

export OMP_NUM_THREADS=1
mpirun -n 28 amplxe-cl -c advanced-hotspots -r amplifier_advanced_hotspots ./test 224 224 6 3.5 0.01 0 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0
mpirun -n 28 amplxe-cl -c hotspots -r amplifier_hotspots ./test 224 224 6 3.5 0.01 0 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0
mpirun -n 28 amplxe-cl -collect hpc-performance -r amplifier_hpc_performance ./test 224 224 6 3.5 0.01 0 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0
mpirun -n 28 advixe-cl -c hotspots --project-dir advisor_hotspots ./test 224 224 6 3.5 0.01 0 0.5 10.0 10.0 12.0 10.0 9.81 0.000001787 0 0 0 0
