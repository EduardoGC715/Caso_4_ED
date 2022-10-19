/*
# include "iStrategy.h"

class BasicStrategy : public iStrategy {
    public:
        BasicStrategy() {
            name = "Basic Strategy";
        }

        void searchTunnel() {
            // Parametros a recibir:
            // Stack<Path> con Path = Door o TNode<Door>
            // y se asume cuenta con un root path
            // Stack<Depth> con Depth = AVL_Node<Chamber>
            // Posiblemente Stack<int> para manejar opciones

            // Proceso:
            // 1. Solicita opciones de top path
            // 2. Descarta opciones ya visitadas
            //     a. Selecciona puerta y avanza
            //         3. Si hay tunel, state = UNDERGROUND
            //            y se agrega al Stack<Depth>
            //     b. Retrocede una puerta
        }

        void searchChamber() {
            // Parametros:
            // Stack<Depth> con Depth = AVL_Node<Chamber>;
            // Posiblemente Stack<int> para manejar opciones

            // Proceso:
            // 1. Solicita opciones de top depth si la camara no ha colapsado
            // 2. Descarta opciones ya visitadas
            //     a. Si no quedan opciones, retrocede (sleep)
            //         4. Si al retroceder la camara colapso, state = UNAVAILABLE
            //     b. Selecciona una opcion y avanza (sleep)
            //         5. Si esta camara ha colapsado, la descarta y retrocede
            //         6. Algoritmo para decidir minar:
            //             a. Decide minar, state = MINING
            //             b. Decide buscar mas profundo

            // Posible simplificacion:
            // Segmentar logica en proceed_door(), retreat_door()
            // proceed_tunnel(), retreat_tunnel(), decide_mining()
        }

        void mineChamber() {
            // Estrategias:
            //     Minar hasta colapsar 1: Spiteful
            //     "Collapse Mining (Fill Inventory - Surface Scouting)"
            //         1. Mina el material de una camara hasta colapsarla y descartarla
            //         2. Si llena inventario al colapsar, state = RETRIEVE
            //         3. Si no llena inventario al colapsar, state = SEARCH
            //         4. State = RETRIEVE si llena inventario antes de colapsar
            //
            //     Minar hasta colapsar 2: Gold Digger/Greedy
            //     "Collapse Mining (Early Return - Deep Scouting)"
            //         1. Mina el material de una camara hasta colapsarla y descartarla
            //         2. Independiente de si llena o no el inventario, state = RETRIEVE
            //
            //     Minar precavido 1: Careful
            //     "Proportional Mining (Fill Inventory - Surface Scouting)"
            //         1. Determina proporcion a minar (Ej. 50% del contenido actual)
            //         2. Tras minar esa cantidad, descarta camara y busca otra (state SEARCH)
            //         3. Si antes de terminar de minar llena inventario (state RETRIEVE)
            //
            //     Minar precavido 2: Spelunker/Bold
            //     "Proportional Mining (Early Return - Deep Scouting)"
            //         1. Determina proporcion a minar
            //         2. Independiente de si llena o no su inventario, (state RETRIEVE)
            //
            //     NOTA:
            //     Posible forma de lograr estrategias similares pero navegacion distinta
            //     IStrategy implements INavigation {proceeds(), retreats()}
            //     DeepNavigation implements INavigation
            //     Strategy1 implements ProportionalStrategy, DeepNavigation
        }

        void retrieveMineral() {

        }

};
*/