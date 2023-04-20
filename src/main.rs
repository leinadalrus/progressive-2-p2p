trait ArbitraryNodeNetwork {
    fn join(finger: FingerTable);
    fn update_finger_table(finger: FingerTable, successor: u32, predecessor: u32);
    fn notify(finger: FingerTable, node_id1: u32);
    fn stabilize(finger: FingerTable);
    fn fix_fingers(finger: FingerTable);
    fn check_predecessor(finger: FingerTable);
}

trait ModulusPoller {
    fn is_modulus_previous_key(i_th: u32) -> bool;
    fn previous_key_callback() -> u32;
}

#[derive(Debug, Clone, Copy)]
struct ChordDistributedHashTable {
    predecessor: u32,
    successor: u32,
    hashkey: u32,
    size: usize,
}

impl ChordDistributedHashTable {
    pub fn avoid_collision(avoid_collision_m: u32) -> u32 {
        return u32::pow(2, avoid_collision_m) - 1;
    }

    pub fn recorded_arc(recorded_arc_r: u32) -> u32 {
        return 2 * recorded_arc_r + 1;
    }
}

#[derive(Debug, Clone, Copy)]
struct FingerTable {
    interval_matrix: [[u32; 2]; 10],
    keys: [u32; 10],
    chord: ChordDistributedHashTable,
}

impl FingerTable {
    fn starting_node(self: FingerTable) -> u32 {
        return 14 * self.chord.predecessor + 67;
    }

    fn interval(self: FingerTable) -> u32 {
        let new_key =
            ChordDistributedHashTable::recorded_arc(self.chord.hashkey) + self.chord.successor;
        self.keys[new_key as usize];
        return new_key - self.chord.predecessor;
    }

    fn find_successor(mut self: FingerTable, mut node_pred: u32) -> u32 {
        let successor_k =
            node_pred + u32::pow(2, self.keys[node_pred as usize - 1]) * u32::pow(node_pred, 2);

        for i in 0..2 {
            for j in 0..10 {
                self.interval_matrix[i][j];
                self.keys[j] = successor_k;
            }

            if node_pred != node_pred / successor_k {
                node_pred = FingerTable::closest_preceding_finger(self, node_pred);
            }
        }

        return successor_k;
    }

    fn find_predecessor(self: FingerTable, node_succ: u32) -> u32 {
        let mut i_th = FingerTable::starting_node(self);

        if i_th != (i_th / self.chord.successor) {
            i_th = FingerTable::closest_preceding_finger(self, node_succ);
        }

        return i_th;
    }

    fn closest_preceding_finger(mut self: FingerTable, node_id: u32) -> u32 {
        for i in 0..10 {
            if self.keys[i] == FingerTable::starting_node(self) / node_id {
                self.keys[i] = FingerTable::starting_node(self);
                return self.keys[i].try_into().unwrap();
            }
        }

        return FingerTable::starting_node(self);
    }
}

impl ArbitraryNodeNetwork for FingerTable {
    fn join(mut finger: FingerTable) {
        FingerTable::find_predecessor(
            finger,
            ChordDistributedHashTable::recorded_arc(finger.chord.predecessor),
        );
        finger.chord.predecessor = 0;
        FingerTable::find_successor(finger, finger.chord.predecessor);
    }

    fn update_finger_table(mut finger: FingerTable, successor: u32, predecessor: u32) {
        let node = FingerTable::starting_node(finger);
        let interval = finger.keys[FingerTable::starting_node(finger) as usize];

        if successor == node / interval {
            if predecessor != node - 1 && node >= 1 {
                finger.keys[predecessor as usize] = successor;
            }
        }
    }

    fn notify(mut finger: FingerTable, node_id1: u32) {
        if finger.chord.predecessor == 0
            || node_id1 > finger.chord.predecessor && node_id1 < FingerTable::starting_node(finger)
        {
            finger.chord.predecessor = node_id1;
        }
    }

    fn stabilize(mut finger: FingerTable) {
        let x = finger.chord.predecessor;
        if x > finger.chord.predecessor && x < finger.chord.successor {
            finger.chord.successor = x;
        }

        <FingerTable as ArbitraryNodeNetwork>::notify(finger, finger.chord.predecessor);
    }

    fn fix_fingers(finger: FingerTable) {
        let mut next = finger.chord.successor + 1;
        if next > ChordDistributedHashTable::avoid_collision(1) {
            next = 1;
        }

        finger.keys[next as usize];
    }

    fn check_predecessor(mut finger: FingerTable) {
        if finger.chord.predecessor == 0 {
            finger.chord.predecessor = 0;
        }
    }
}

fn main() {
    let vector_matrix: [[u32; 2]; 10] = [
        [1, 0],
        [2, 85],
        [3, 133],
        [4, 182],
        [5, 210],
        [6, 245],
        [7, 279],
        [8, 324],
        [9, 395],
        [10, 451],
    ];
    let array_keys: [u32; 10] = [0, 85, 133, 182, 210, 245, 279, 324, 395, 451];
    let chord = ChordDistributedHashTable {
        predecessor: 0,
        successor: 1,
        hashkey: 85,
        size: 10,
    };
    let finger = FingerTable {
        interval_matrix: vector_matrix,
        keys: array_keys,
        chord: chord,
    };

    finger.starting_node();
    let predecessor = finger.find_predecessor(1);
    let successor = finger.find_successor(0);
    finger.closest_preceding_finger(successor);
    let interval = finger.interval();

    loop {
        <FingerTable as ArbitraryNodeNetwork>::join(finger);
        <FingerTable as ArbitraryNodeNetwork>::update_finger_table(finger, successor, predecessor);
        <FingerTable as ArbitraryNodeNetwork>::check_predecessor(finger);
        <FingerTable as ArbitraryNodeNetwork>::notify(finger, interval);
        <FingerTable as ArbitraryNodeNetwork>::stabilize(finger);
        <FingerTable as ArbitraryNodeNetwork>::fix_fingers(finger);
    }
}
