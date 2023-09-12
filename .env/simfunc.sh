# current simulation called
SIM_CUR="."

# sim [option] function to call and interact with different simulations
function sim() {

    # setting the user call to the correct directory
    if [[ $(pwd) != ${SIM_ROOT} ]]; then
        printf "\"sim\" command evoked from wrong directory.\nRun the command from \"%s\".\n" ${SIMROOT}
        return 0
    fi

    case $1 in

        call)
            SIM_CALL=$2

            # delete ./simulation directory if it already exists
            if [[ -d "$SIM_DIR" ]]; then
                rm -rf ${SIM_DIR}
            fi
            
            mkdir ${SIM_DIR}
            case "${SIM_CALL}" in
                utils-matrix)
                    DEST="${SRC_DIR}/utils/matrix"
                    __call_simulation ${SIM_CALL} ${DEST}
                    __create_symlinks
                    ;;
                utils-array)
                    DEST="${SRC_DIR}/utils/array"
                    __call_simulation ${SIM_CALL} ${DEST}
                    __create_symlinks
                    ;;
                projectile-3d)
                    DEST="${SRC_DIR}/Projectile/3d"
                    __call_simulation ${SIM_CALL} ${DEST}
                    __create_symlinks "src/sim.input"
                    ;;
                projectile-2d)
                    DEST="${SRC_DIR}/Projectile/2d"
                    __call_simulation ${SIM_CALL} ${DEST}
                    __create_symlinks "src/sim.input"
                    ;;
                gameoflife)
                    DEST="${SRC_DIR}/GameOfLife"
                    __call_simulation ${SIM_CALL} ${DEST}
                    __create_symlinks "src/sim.input"
                    ;;
                *)
                    if [[ -z "${SIM_CALL}" ]]; then
                        echo "Enter a simulation name"
                        return 0
                    fi
                    echo "No such simulation found"
                    return 0
                    ;;
            esac
            ;;

        run)
            cd ${SIM_DIR} || return 0
            make
            ./main
            cd ../
            ;;

        build | compile )
            cd ${SIM_DIR} || return 0
            make
            cd ../
            ;;

        make)
            cd ${SIM_DIR} || return 0
            make $2
            cd ../
            ;;

        clean)
            if [[ -d "$SIM_DIR" ]]; then
                rm -rf ${SIM_DIR}
                printf "Removed %s\n" "${SIM_DIR}"
            else
                printf "%s did not exist\n" "${SIM_DIR}"
            fi
            SIM_CALL="."
            ;;

        anim)
            if [[ ! -d "${SIM_DIR}/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            if [[ ! -f "${SIM_DIR}/vis/animate.py" ]]; then
                echo "No animator module found in current simulation!"
                return 0
            fi
            if [[ -d "${SIM_DIR}/dumps/" ]]; then
                python3 ${SIM_DIR}/vis/animate.py ${SIM_DIR}/dumps
                return 0
            fi
            if [[ -f "${SIM_DIR}/dump.out" ]]; then
                python3 ${SIM_DIR}/vis/animate.py ${SIM_DIR}/dump.out
                return 0
            fi
            ;;

        plot)
            if [[ ! -d "${SIM_DIR}/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            if [[ ! -f "${SIM_DIR}/vis/plot.py" ]]; then
                echo "No plotting module found in current simulation!"
                return 0
            fi
            if [[ -d "${SIM_DIR}/dumps/" ]]; then
                python3 ${SIM_DIR}/vis/animate.py ${SIM_DIR}/dumps
                return 0
            fi
            if [[ -f "${SIM_DIR}/dump.out" ]]; then
                python3 ${SIM_DIR}/vis/animate.py ${SIM_DIR}/dump.out
                return 0
            fi
            ;;
        
        which)
            printf "Current simulation called in %s is [%s].\n" "${SIM_DIR}" "${SIM_CUR}"
            ;;

        *)
            echo "Not a valid input"
            ;;
    esac
}

function __call_simulation() {
    SIM_CALL=$1
    DEST=$2
    
    rsync -a ${DEST}/* ${SIM_DIR} \
        --exclude tests/
    printf "%s called in %s.\n" "${SIM_CALL}" "${SIM_DIR}"
    if [[ -e ${DEST}/${DEPS} ]]; then
        while IFS= read -r LINE; do
            TARG="$(basename ${LINE})"
            rsync -a ${SRC_DIR}/${LINE}src/* ${SIM_DIR}/src \
                --exclude 'main.c'
            printf "...Copied dependency [%s] into %s/src\n" "${TARG}" "${SIM_DIR}"
        done < ${DEST}/${DEPS}
    fi
    SIM_CUR="${SIM_CALL}"
    echo Done!
}

function __create_symlinks() {
    if [[ $# -eq 0 ]]; then
        return 0
    fi

    for i in "$@"; do
        if [[ ! -f ${SIM_DIR}/${i} ]]; then
            echo "${SIM_DIR}/${i} not found..."
            continue
        fi
        mv "${SIM_DIR}/${i}" "${SIM_DIR}/${i##*/}" 
        ln -P "${SIM_DIR}/${i##*/}" "${SIM_DIR}/${i}" 
        printf "created hard link %s/%s\n" "${i##*/}" "${SIM_DIR}" 
    done
}
