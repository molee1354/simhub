function sim() {
    case $1 in
        run)
            cd ./simulation
            make
            ./main
            cd ../
            ;;
        make)
            cd ./simulation
            make
            cd ../
            ;;
        anim)
            if [[ ! -d "./simulation/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            python3 ./simulation/vis/animate.py ./simulation/dump.out
            ;;
        plot)
            if [[ ! -d "./simulation/vis/" ]]; then
                echo "No visualization module found in current simulation!"
                return 0
            fi
            python3 ./simulation/vis/plot.py ./simulation/dump.out

            ;;
        *)
            echo "Not a valid input"
            ;;
    esac
}
