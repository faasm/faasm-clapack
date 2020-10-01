import os

from multiprocessing import cpu_count
from os.path import join, dirname, realpath
from subprocess import run
from copy import copy

from invoke import task


PROJ_ROOT = dirname(realpath(__file__))
THIRD_PARTY_DIR = join(PROJ_ROOT, "third-party")

N_CPUS = int(cpu_count()) - 1


@task
def lapacke(ctx, clean=False):
    """
    Builds the LAPACKE interface from LAPACK
    """
    lapacke_dir = join(THIRD_PARTY_DIR, "lapack", "LAPACKE")

    if clean:
        run("make clean", cwd=lapacke_dir, shell=True, check=True)

    run("make -j {}".format(N_CPUS), shell=True, cwd=lapacke_dir, check=True)
    run("make install", shell=True, cwd=lapacke_dir, check=True)


@task
def clapack(ctx, clean=False, shared=False):
    """
    Builds CBLAS, CLAPACK, F2C etc.
    """
    clapack_dir = join(THIRD_PARTY_DIR, "clapack")

    # Build clapack
    if clean:
        run("make clean", cwd=clapack_dir, shell=True, check=True)

    # Set up environment to specify whether we're building static or shared
    env = copy(os.environ)
    env.update({"LIBEXT": ".so" if shared else ".a"})

    # Make libf2c first (needed by others)
    run(
        "make f2clib -j {}".format(N_CPUS),
        shell=True,
        cwd=clapack_dir,
        check=True,
        env=env,
    )

    # Make the rest of CLAPACK
    run(
        "make -j {}".format(N_CPUS),
        shell=True,
        cwd=clapack_dir,
        check=True,
        env=env,
    )
    run("make install", shell=True, cwd=clapack_dir, check=True)
