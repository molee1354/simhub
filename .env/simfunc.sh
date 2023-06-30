# project root
export SIMROOT=$(pwd)

# sim [option] function to call and interact with different simulations
function sim() {
    if [[ $(pwd) != ${SIMROOT} ]]; then
        printf "\"sim\" command evoked from wrong directory.\nRun the command from \"%s\".\n" ${SIMROOT}
        return
    fi
    SIM_DIR="./simulation"
    SRC_DIR="./source"
    DEPS="require"

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
                    rsync -a ${SRC_DIR}/utils/matrix/* ${SIM_DIR} \
                        --exclude tests/
                    printf "%s called in %s.\n" "${SIM_CALL}" "${SIM_DIR}"
                    ;;
                utils-array)
                    rsync -a ${SRC_DIR}/utils/array/* ${SIM_DIR} \
                        --exclude tests/
                    printf "%s called in %s.\n" "${SIM_CALL}" "${SIM_DIR}"
                    ;;
                projectile-3d)
                    cp -r ${SRC_DIR}/Projectile/3d/* ${SIM_DIR}
                    printf "%s called in %s.\n" "${SIM_CALL}" "${SIM_DIR}"
                    ;;
                projectile-2d)
                    cp -r ${SRC_DIR}/Projectile/2d/* ${SIM_DIR}
                    printf "%s called in %s.\n" "${SIM_CALL}" "${SIM_DIR}"
                    ;;
                gameoflife)
                    DEST="${SRC_DIR}/GameOfLife"
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
                    echo Done!
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
            ;;

        anim)
            if [[ ! -d "${SIM_DIR}/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            python3 ${SIM_DIR}/vis/animate.py ${SIM_DIR}/dump.out
            ;;

        plot)
            if [[ ! -d "${SIM_DIR}/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            python3 ${SIM_DIR}/vis/plot.py ${SIM_DIR}/dump.out

            ;;
        *)
            echo "Not a valid input"
            ;;
    esac
}
