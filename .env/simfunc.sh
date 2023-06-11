function sim() {
    SIM_DIR="./simulation"

    case $1 in

        call)
            SIM_CALL=$2

            # delete ./simulation directory if it already exists
            if [[ -d "$SIM_DIR" ]]; then
                rm -rf ${SIM_DIR}
            fi
            
            mkdir ${SIM_DIR}
            case "${SIM_CALL}" in
                matrix)
                    cp -r ./source/Matrix/* ${SIM_DIR}
                    printf "%s called in %s.\n" ${SIM_CALL} ${SIM_DIR}
                    ;;
                linkedlist)
                    cp -r ./source/LinkedList/* ${SIM_DIR}
                    printf "%s called in %s.\n" ${SIM_CALL} ${SIM_DIR}
                    ;;
                projectile-3d)
                    cp -r ./source/Projectile/3d/* ${SIM_DIR}
                    printf "%s called in %s.\n" ${SIM_CALL} ${SIM_DIR}
                    ;;
                projectile-2d)
                    cp -r ./source/Projectile/2d/* ${SIM_DIR}
                    printf "%s called in %s.\n" ${SIM_CALL} ${SIM_DIR}
                    ;;
                *)
                    if [[ -z "${SIM_CALL}" ]]; then
                        echo "Enter a simulation name"
                        return
                    fi
                    echo "No such simulation found"
                    ;;
            esac
            ;;
        run)
            cd ${SIM_DIR}
            make
            ./main
            cd ../
            ;;
        make)
            cd ${SIM_DIR}
            make
            cd ../
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
