use bevy::{
    math::Vec3Swizzles, prelude::*, sprite::MaterialMesh2dBundle,
    DefaultPlugins,
};

pub enum ModulusPolling {
    PreviousKey { is_remainder_previous_key: bool },
    EntityRemoved,
    NotPresent,
}

pub trait ModulusPoller {
    fn is_modulus_previous_key(i_th: u32) -> bool;
    fn previous_key_callback() -> u32;
}

pub trait ArbitraryNodeNetwork {
    fn join(finger: FingerTable);
    fn update_finger_table(
        finger: FingerTable, successor: u32, predecessor: u32,
    );
    fn notify(finger: FingerTable, node_id1: u32);
    fn stabilize(finger: FingerTable);
    fn fix_fingers(finger: FingerTable);
    fn check_predecessor(finger: FingerTable);
}

#[derive(Debug, Clone, Copy)]
pub struct DistributedHashTable {
    predecessor: u32,
    successor: u32,
    hashkey: u32,
    size: usize,
}

impl DistributedHashTable {
    pub fn avoid_collision(avoid_collision_m: u32) -> u32 {
        return u32::pow(2, avoid_collision_m) - 1;
    }

    pub fn recorded_arc(recorded_arc_r: u32) -> u32 {
        return 2 * recorded_arc_r + 1;
    }
}

#[derive(Debug, Clone, Copy)]
pub struct FingerTable {
    interval_matrix: [[u32; 2]; 10],
    keys: [u32; 10],
    dht: DistributedHashTable,
}

impl FingerTable {
    fn starting_node(self: FingerTable) -> u32 {
        return 14 * self.dht.predecessor + 67;
    }

    fn interval(self: FingerTable) -> u32 {
        let new_key = DistributedHashTable::recorded_arc(self.dht.hashkey)
            + self.dht.successor;
        self.keys[new_key as usize];
        return new_key - self.dht.predecessor;
    }

    fn find_successor(mut self: FingerTable, mut node_pred: u32) -> u32 {
        let successor_k = node_pred
            + u32::pow(2, self.keys[node_pred as usize - 1])
                * u32::pow(node_pred, 2);

        for i in 0..2 {
            for j in 0..10 {
                self.interval_matrix[i][j];
                self.keys[j] = successor_k;
            }

            if node_pred != node_pred / successor_k {
                node_pred =
                    FingerTable::closest_preceding_finger(self, node_pred);
            }
        }

        return successor_k;
    }

    fn find_predecessor(self: FingerTable, node_succ: u32) -> u32 {
        let mut i_th = FingerTable::starting_node(self);

        if i_th != (i_th / self.dht.successor) {
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
            DistributedHashTable::recorded_arc(finger.dht.predecessor),
        );
        finger.dht.predecessor = 0;
        FingerTable::find_successor(finger, finger.dht.predecessor);
    }

    fn update_finger_table(
        mut finger: FingerTable, successor: u32, predecessor: u32,
    ) {
        let node = FingerTable::starting_node(finger);
        let interval = finger.keys[FingerTable::starting_node(finger) as usize];

        if successor == node / interval {
            if predecessor != node - 1 && node >= 1 {
                finger.keys[predecessor as usize] = successor;
            }
        }
    }

    fn notify(mut finger: FingerTable, node_id1: u32) {
        if finger.dht.predecessor == 0
            || node_id1 > finger.dht.predecessor
                && node_id1 < FingerTable::starting_node(finger)
        {
            finger.dht.predecessor = node_id1;
        }
    }

    fn stabilize(mut finger: FingerTable) {
        let x = finger.dht.predecessor;
        if x > finger.dht.predecessor && x < finger.dht.successor {
            finger.dht.successor = x;
        }

        <FingerTable as ArbitraryNodeNetwork>::notify(
            finger,
            finger.dht.predecessor,
        );
    }

    fn fix_fingers(finger: FingerTable) {
        let mut next = finger.dht.successor + 1;
        if next > DistributedHashTable::avoid_collision(1) {
            next = 1;
        }

        finger.keys[next as usize];
    }

    fn check_predecessor(mut finger: FingerTable) {
        if finger.dht.predecessor == 0 {
            finger.dht.predecessor = 0;
        }
    }
}

#[derive(Component)]
pub struct ArbitraryNode {
    finger_table: FingerTable,
}

#[derive(Component)]
pub struct ChordRadial {
    rotation_speed: f32,
}

#[derive(Component)]
pub struct SnapsTowardsChord;

#[derive(Component)]
pub struct RotatesAroundChord {
    pub rotation_speed: f32,
}

fn startup_setup(mut commands: Commands) {
    commands.spawn(Camera2dBundle::default());
}

fn bundle_material_mesh(
    mut commands: Commands, mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<ColorMaterial>>,
) {
    commands.spawn(MaterialMesh2dBundle {
        mesh: meshes.add(shape::Circle::new(50.).into()).into(),
        material: materials.add(ColorMaterial::from(Color::PURPLE)),
        transform: Transform::from_translation(Vec3::new(-150., 0., 0.)),
        ..default()
    });
}

fn load_entity_handle(mut commands: Commands, asset_server: Res<AssetServer>) {
    let chord_shape_handle = asset_server.load("assets/images/circle.png");
    let chord_node_entity_handle =
        asset_server.load("assets/images/circle.png");

    commands.spawn((
        SpriteBundle {
            texture: chord_shape_handle,
            ..default()
        },
        ChordRadial {
            rotation_speed: f32::to_radians(360.0),
        },
    ));

    commands.spawn((
        SpriteBundle {
            texture: chord_node_entity_handle,
            ..default()
        },
        RotatesAroundChord {
            rotation_speed: f32::to_radians(360.0),
        },
    ));
}

fn entity_rotation_system(mut query: Query<(&ChordRadial, &mut Transform)>) {
    let delta_time = 1.0 / 60.0;
    let chord_boundary = Vec2::new(1.0, 1.0);

    let (chord_node_entity, mut transform) = query.single_mut();
    let rotation_factor = 0.0;

    transform.rotate_z(
        rotation_factor * chord_node_entity.rotation_speed * delta_time,
    );

    let varied_chord_boundary = Vec3::from((chord_boundary / 2.0, 0.0));

    transform.translation = transform
        .translation
        .min(varied_chord_boundary)
        .max(-varied_chord_boundary);
}

fn transform_entity_query(
    mut query: Query<
        &mut Transform,
        (With<SnapsTowardsChord>, Without<ChordRadial>),
    >,
    chord_query: Query<&Transform, With<ChordRadial>>,
) {
    let node_properties = chord_query.single();
    let node_translation = node_properties.translation.xy();

    for mut chord_node_entity in &mut query {
        let within_towards_centre =
            (node_translation - chord_node_entity.translation.xy()).normalize();
        let nodes_rotate_within_chord =
            Quat::from_rotation_arc(Vec3::Y, within_towards_centre.extend(0.0));
        chord_node_entity.rotation = nodes_rotate_within_chord;
    }
}

fn execute_arbitrary_network_command(
    mut query: Query<
        (&RotatesAroundChord, &mut Transform),
        Without<ChordRadial>,
    >,
    chord_query: Query<&Transform, With<ChordRadial>>,
    mut arbitrary_query: Query<&mut ArbitraryNode>,
) {
    let delta_time = 1.0 / 60.0;

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
    let dht = DistributedHashTable {
        predecessor: 0,
        successor: 1,
        hashkey: 85,
        size: 10,
    };
    // let finger = FingerTable {
    //     interval_matrix: vector_matrix,
    //     keys: array_keys,
    //     dht,
    // };

    let chord_transform = chord_query.single();
    let chord_translation = chord_transform.translation.xyz();

    for (rotator, mut transformer) in &mut query {
        let node_fwd = (transformer.translation.xy()).normalize();
        let translates_within_chord =
            (chord_translation - transformer.rotation * Vec3::Y).xy();
        let fwd_chord_dot = node_fwd.dot(translates_within_chord);

        let node_offsetted = (transformer.rotation * Vec3::X).xy();
        let offsetted_chord_dot = node_offsetted.dot(translates_within_chord);

        let signed_rotation = -f32::copysign(1.0, offsetted_chord_dot);
        let max_angle = fwd_chord_dot.clamp(-1.0, 1.0).acos();

        let rotation_angle = signed_rotation
            * (rotator.rotation_speed * delta_time).min(max_angle);
        transformer.rotate_z(rotation_angle);
    }

    for mut arbitrary_node in &mut arbitrary_query {
        arbitrary_node.finger_table.interval_matrix = vector_matrix;
        arbitrary_node.finger_table.keys = array_keys;
        arbitrary_node.finger_table.dht = dht;
        
        arbitrary_node.finger_table.starting_node();

        let predecessor = arbitrary_node.finger_table.find_predecessor(85);
        let successor = arbitrary_node.finger_table.find_successor(0);
        arbitrary_node
            .finger_table
            .closest_preceding_finger(successor);
        let interval = arbitrary_node.finger_table.interval();

        <FingerTable as ArbitraryNodeNetwork>::join(
            arbitrary_node.finger_table,
        );
        <FingerTable as ArbitraryNodeNetwork>::update_finger_table(
            arbitrary_node.finger_table,
            successor,
            predecessor,
        );
        <FingerTable as ArbitraryNodeNetwork>::check_predecessor(
            arbitrary_node.finger_table,
        );
        <FingerTable as ArbitraryNodeNetwork>::notify(
            arbitrary_node.finger_table,
            interval,
        );
        <FingerTable as ArbitraryNodeNetwork>::stabilize(
            arbitrary_node.finger_table,
        );
        <FingerTable as ArbitraryNodeNetwork>::fix_fingers(
            arbitrary_node.finger_table,
        );
    }
}

fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_startup_system(startup_setup)
        .add_system(bundle_material_mesh)
        .add_system(load_entity_handle)
        .add_system(entity_rotation_system)
        .add_system(transform_entity_query)
        .add_system(execute_arbitrary_network_command)
        .run();
}
