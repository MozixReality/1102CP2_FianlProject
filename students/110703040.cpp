#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#define test 0
#if test
    #define t(any) any
#else
    #define t(any) (void)0;
#endif

#ifndef TYPENAMES
#define TYPENAMES
    typedef int32_t S32; // distance, position, round, point
    struct stats;
    struct vertex;
    struct control;
#endif//TYPENAMES

#ifndef CONSTANTS
#define CONSTANTS
    static S32 S32_MIN = 0x80000000;
    static char UNVISITED = 'U';
    static char VISITED = 'V';

    static S32 DIR[4][2] = 
    {
        {1, 0},     // down 0
        {0, 1},     // right 1
        {-1, 0},    // up 2
        {0, -1}     // left 3
    };

    static S32 DIR_I = 0;
    static S32 DIR_J = 1;

    static const char *DIR_STR_0 = "DOWN";
    static const char *DIR_STR_1 = "RIGHT";
    static const char *DIR_STR_2 = "UP";
    static const char *DIR_STR_3 = "LEFT";
#endif//CONSTANTS

struct stats {
    S32 round; 
    S32 map_sizeI;
    S32 map_sizeJ;

    S32 self_posI;
    S32 self_posJ;
    S32 rival_posI;
    S32 rival_posJ;

    double self_points;
    double rival_points;

    char self_flag;
    char rival_flag;

    vector<string> map;

    void print() const
    {
        printf("==== stats ====\n");

        printf("round         | %d\n", round);

        printf("map_size I, J | %d, %d\n", map_sizeI, map_sizeJ);

        printf("map --\n");
        for (S32 I = 0; I < map_sizeI; I++)
        {
            for (S32 J = 0; J < map_sizeJ; J++)
                printf("%c ", map[I][J]);
            printf("\n");
        }
        printf("--- --\n");

        printf("self  [%c] {%d, %d} | %.2lf points\n", self_flag, self_posI, self_posJ, self_points);
        printf("rival [%c] {%d, %d} | %.2lf points\n", rival_flag, rival_posI, rival_posJ, rival_points);

        printf("==== ===== ====\n");
    }

    static stats& get()
    {
        static stats Stats;
        return Stats;
    }

private:
    stats()
    {
        scanf("%d %d %d", &round, &map_sizeI, &map_sizeJ);

        map.resize(map_sizeI);
        for (S32 I = map_sizeI; I--;)
            map[I] = string(map_sizeJ, '-');

        for (S32 I = 0; I < map_sizeI; I++)
        {
            char* T = &map[I][0];
            while (*T)
                scanf("%*c%c", T++);
        }

        double A_points, B_points;

        scanf("%lf %lf %c", &A_points, &B_points, &self_flag);

        if (self_flag == 'A')
        {
            self_points = A_points;
            rival_flag = 'B';
            rival_points = B_points;
        }
        else if (self_flag == 'B')
        {
            self_points = B_points;
            rival_flag = 'A';
            rival_points = A_points;
        }

        for (self_posI = map_sizeI; self_posI--;)
            for (self_posJ = map_sizeJ; self_posJ--;)
                if (map[self_posI][self_posJ] == self_flag)
                    goto sect_1;
sect_1: 
        for (rival_posI = map_sizeI; rival_posI--;)
            for (rival_posJ = map_sizeJ; rival_posJ--;)
                if (map[rival_posI][rival_posJ] == rival_flag)
                    goto sect_2;
sect_2:
        return;
    }
};

struct vertex {
    S32 pos_i;
    S32 pos_j;
    S32 src_i;
    S32 src_j;
    S32 dist;
    double points;

    char flag;
    char state;

    vertex()
        : pos_i(-1), pos_j(-1)
        , src_i(-1), src_j(-1)
        , dist(1)
        , points((double)S32_MIN) 
        , flag('\0')
        , state(UNVISITED) {}

    vertex(
        S32 _pos_i, S32 _pos_j,
        S32 _src_i, S32 _src_j,
        S32 _dist, 
        double _points,
        char _flag,
        char _state)
        :   pos_i(_pos_i), pos_j(_pos_j)
        ,   src_i(_src_i), src_j(_src_j)
        ,   dist(_dist)
        ,   points(_points)
        ,   flag(_flag)
        ,   state(_state) {}

    void print() const
    {
        printf("{%d, %d} <- {%d, %d} | %.2lf / %d | [flag %c] | [state %c]\n"
        , pos_i, pos_j
        , src_i, src_j
        , points
        , dist
        , flag
        , state);
    }

    friend vertex& bigger_vertex(
        vertex& _lhs,
        vertex& _rhs)
    {
    // not to choose init state and player vertex
        if (_lhs.dist == 0) return _rhs;
        if (_rhs.dist == 0) return _lhs;
        if (_lhs.points == (double)S32_MIN) return _rhs;
        if (_rhs.points == (double)S32_MIN) return _lhs;

    // choose vertex with bigger points
        return (_lhs.points > _rhs.points) ? (_lhs) : (_rhs);
    }
};

struct control {
    void walk()
    {
        fill_points();

    // get the biggest and closer vertex
        vertex* max_vertex = &vertex_matrix[0][0];

        for (S32 I = stats::get().map_sizeI; I--;)
        {
            for (S32 J = stats::get().map_sizeJ; J--;)
            {
                t(vertex_matrix[I][J].print();)

                max_vertex 
                = &bigger_vertex(*max_vertex, vertex_matrix[I][J]);
            }
            t(printf("\n");)
        }
        
    // trace back to the position of self from max_vertex
        while (reachable(
                max_vertex->src_i, 
                max_vertex->src_j))
        {
            t(max_vertex->print();)

            max_vertex 
            = &vertex_matrix
                [max_vertex->src_i]
                [max_vertex->src_j];
        }

        t(max_vertex->print();)

    // calculate the facing direction when stepping out
        for (S32 D = 4; D--;)
        {
            if (max_vertex->pos_i - max_vertex->src_i == DIR[D][DIR_I] &&
                max_vertex->pos_j - max_vertex->src_j == DIR[D][DIR_J])
            {
                t(printf("walk_1 %d\n", D);)
                switch (D)
                {
                    case 0:
                        printf("%s\n", DIR_STR_0);
                        return;
                    case 1:
                        printf("%s\n", DIR_STR_1);
                        return;
                    case 2:
                        printf("%s\n", DIR_STR_2);
                        return;
                    case 3:
                        printf("%s\n", DIR_STR_3);
                        return;
                }
            }
        }
    // no path is found : random walk
        random_walk();
    }

    static control& get()
    {
        static control Control;
        return Control;
    }

private:
    control()
    {
    // init all vertices
        vertex_matrix.resize(stats::get().map_sizeI);
        for (S32 I = stats::get().map_sizeI; I--;)
            vertex_matrix[I].resize(stats::get().map_sizeJ);

        fill_deadlane();
    }

    vector<vector<vertex> > vertex_matrix;
    queue<vertex *> vertex_ref_queue;
    vector<vector<S32> > deadlane;

    void fill_points()
    {
        vertex_matrix
            [stats::get().self_posI]
            [stats::get().self_posJ]
        = vertex(
            stats::get().self_posI,
            stats::get().self_posJ,
            -1, -1,
            0,
            stats::get().self_points,
            stats::get().self_flag,
            UNVISITED);
        
        vertex_ref_queue.push(
            &vertex_matrix
                [stats::get().self_posI]
                [stats::get().self_posJ]);

        while (! vertex_ref_queue.empty())
        {
            vertex* NOW = vertex_ref_queue.front();
            vertex_ref_queue.pop();

            NOW->state = VISITED;

        // try to push four-dir neighbors
            for (S32 D = 4; D--;)
            {
                S32 expand_posI = NOW->pos_i + DIR[D][DIR_I];
                S32 expand_posJ = NOW->pos_j + DIR[D][DIR_J];

                if (reachable(expand_posI, expand_posJ)) // 1., 2.
                {
                // 3. not source (cycle detection)
                    vertex* COPY_NOW = NOW;
                    bool cycle = false;

                    while (reachable(
                            COPY_NOW->src_i,
                            COPY_NOW->src_j))
                    {
                        if (expand_posI == COPY_NOW->src_i &&
                            expand_posJ == COPY_NOW->src_j) 
                        {
                            cycle = true;
                            break;
                        }

                        COPY_NOW 
                        = &vertex_matrix
                            [COPY_NOW->src_i]
                            [COPY_NOW->src_j];
                    }

                    if (cycle) continue;
                
                // 4. not to be stuck in deadlane ???
                // 4-1. now at entry ???
                // 4-2. try to expand to deadlane
                // 4-3. have no enough steps to escape : unwilling to to enter

                    if (shortest_pathlength_to_rival(
                            stats::get().self_posI,
                            stats::get().self_posJ) <
                        2 * deadlane
                            [stats::get().self_posI]
                            [stats::get().self_posJ] + 
                        2 * positive_or_zero(
                            deadlane
                                [expand_posI]
                                [expand_posJ] -
                            deadlane
                                [stats::get().self_posI]
                                [stats::get().self_posJ]))
                    {
                        t(printf("continue at <%d, %d>\n", expand_posI, expand_posJ);)
                        continue;
                    }

                // new_vertex : ready to compare and update
                    vertex new_vertex(
                        expand_posI, 
                        expand_posJ, 
                        NOW->pos_i, 
                        NOW->pos_j, 
                        NOW->dist, 
                        NOW->points,
                        stats::get().map
                            [expand_posI]
                            [expand_posJ],
                        vertex_matrix
                            [expand_posI]
                            [expand_posJ].state);

                // encouraging : 
                // 1. closer to self is better
                // 2. points fade with distance
                    S32 closeness 
                    = shortest_pathlength_to_rival(expand_posI, expand_posJ) - (new_vertex.dist + 1);

                    switch (new_vertex.flag)
                    {
                        case '.':
                            new_vertex.dist += 1;
                            break;
                        case 'b':
                            new_vertex.dist += 4;
                            break;
                        case 'm':
                            new_vertex.dist += 1;
                            new_vertex.points += (
                                1.0 * closeness) / 
                                new_vertex.dist;
                            break;
                        case 'n':
                            new_vertex.dist += 1;
                            new_vertex.points += -(
                                1.0 * closeness) / 
                                new_vertex.dist;
                            break;
                        case 's':
                            new_vertex.dist += 1;
                            new_vertex.points += 1.0 * new_vertex.points * (
                                1.0 * closeness) / 
                                new_vertex.dist;
                            break;
                        case 't':
                            new_vertex.dist += 1;
                            new_vertex.points += -0.5 * new_vertex.points * (
                                1.0 * closeness) / 
                                new_vertex.dist;
                            break;
                    }

                // update to the max : regardless of state
                    vertex_matrix
                        [expand_posI]
                        [expand_posJ]
                    = bigger_vertex(
                        new_vertex,
                        vertex_matrix
                            [expand_posI]
                            [expand_posJ]);
                        
                // if unvisited, push to FIFO to be visited
                    if (vertex_matrix
                            [expand_posI]
                            [expand_posJ].state == UNVISITED)
                    {
                        vertex_ref_queue.push(
                            &vertex_matrix
                                [expand_posI]
                                [expand_posJ]);
                    }
                }
            }
        }
    }

    void fill_deadlane()
    {
        deadlane.resize(stats::get().map_sizeI);
        for (S32 I = stats::get().map_sizeI; I--;)
            deadlane[I].resize(stats::get().map_sizeJ);

        for (S32 I = stats::get().map_sizeI; I--;)
        {
            for (S32 J = stats::get().map_sizeJ; J--;)
            {
                if (! inbound(I, J) ||
                    stats::get().map[I][J] == 'x') continue;

                S32 obstacle = 4;
                for (S32 d = 4; d--;)
                {
                    if (inbound(
                            I + DIR[d][DIR_I],
                            J + DIR[d][DIR_J]) && 
                        stats::get().map
                            [I + DIR[d][DIR_I]]
                            [J + DIR[d][DIR_J]] != 'x')
                    {
                        obstacle--;
                    }
                }

                if (obstacle >= 2) 
                    deadlane[I][J] = obstacle << 28;
            }
        }

        for (S32 I = 0; I < stats::get().map_sizeI; I++)
        {
            for (S32 J = 0; J < stats::get().map_sizeJ; J++)
            {
                t(printf("%d ", deadlane[I][J] >> 28);)
            }
            t(printf("\n");)
        }
        t(printf("==== ===== ====\n");)

        for (S32 I = stats::get().map_sizeI; I--;)
            for (S32 J = stats::get().map_sizeJ; J--;)
                if ((deadlane[I][J] >> 28) == 3)
                    fill_deadlane_1(I, J);

        for (S32 I = 0; I < stats::get().map_sizeI; I++)
        {
            for (S32 J = 0; J < stats::get().map_sizeJ; J++)
            {
                t(printf("%d ", 0x0fffffff & deadlane[I][J]);)
            }
            t(printf("\n");)
        }
        t(printf("==== ===== ====\n");)

        for (S32 I = stats::get().map_sizeI; I--;)
            for (S32 J = stats::get().map_sizeJ; J--;)
                if ((deadlane[I][J] >> 28) == 3)
                    fill_deadlane_2(I, J, deadlane[I][J] & 0x0fffffff);
                else
                    deadlane[I][J] &= 0x0fffffff;

        for (S32 I = 0; I < stats::get().map_sizeI; I++)
        {
            for (S32 J = 0; J < stats::get().map_sizeJ; J++)
            {
                t(printf("%d ", deadlane[I][J]);)
            }
            t(printf("\n");)
        }
        t(printf("==== ===== ====\n");)
    }

    S32 fill_deadlane_1(S32 _i, S32 _j, S32 _depth = 1)
    {
        if (! inbound(_i, _j)) return 0; 
        if (deadlane[_i][_j] == 0 || 
            (deadlane[_i][_j] & 0x80000000)) return 0;

        deadlane[_i][_j] |= 0x80000000;
        
        S32 track = 
            fill_deadlane_1(_i + DIR[0][DIR_I], _j + DIR[0][DIR_J], _depth + 1) + 
            fill_deadlane_1(_i + DIR[1][DIR_I], _j + DIR[1][DIR_J], _depth + 1) +
            fill_deadlane_1(_i + DIR[2][DIR_I], _j + DIR[2][DIR_J], _depth + 1) +
            fill_deadlane_1(_i + DIR[3][DIR_I], _j + DIR[3][DIR_J], _depth + 1);

        return (track) ? 
            (deadlane[_i][_j] = deadlane[_i][_j] & 0x70000000 | track) :
            (deadlane[_i][_j] = deadlane[_i][_j] & 0x70000000 | _depth);
    }

    S32 fill_deadlane_2(S32 _i, S32 _j, S32 _depth)
    {
        if (! inbound(_i, _j)) return 0; 
        if (deadlane[_i][_j] == 0 || 
            (deadlane[_i][_j] & 0x80000000)) return 0;

        deadlane[_i][_j] |= 0x80000000;
        
        S32 track = 
            fill_deadlane_2(_i + DIR[0][DIR_I], _j + DIR[0][DIR_J], _depth - 1) + 
            fill_deadlane_2(_i + DIR[1][DIR_I], _j + DIR[1][DIR_J], _depth - 1) +
            fill_deadlane_2(_i + DIR[2][DIR_I], _j + DIR[2][DIR_J], _depth - 1) +
            fill_deadlane_2(_i + DIR[3][DIR_I], _j + DIR[3][DIR_J], _depth - 1);

        deadlane[_i][_j] = _depth;

        return track;
    }

    S32 positive_or_zero(S32 _n)
    {
        return (_n > 0) ? (_n) : (0);
    }

    bool inbound(
        S32 _pos_i, 
        S32 _pos_j)
    {
        return
            _pos_i < stats::get().map_sizeI && 
            _pos_i > -1 &&
            _pos_j < stats::get().map_sizeJ && 
            _pos_j > -1;
    }

    bool reachable(
        S32 _pos_i, 
        S32 _pos_j)
    {
        return
        // 1. no outbounding 
            inbound(_pos_i, _pos_j) &&
        // 2. not unreachable
            stats::get().map[_pos_i][_pos_j] != 'x' &&
            stats::get().map[_pos_i][_pos_j] != 'A' && 
            stats::get().map[_pos_i][_pos_j] != 'B';
    }

    void random_walk()
    {
        for (S32 d = 4; d--;)
        {
            S32 D = (stats::get().round + d) % 4;

            if (reachable(
                    stats::get().self_posI + DIR[D][DIR_I],
                    stats::get().self_posJ + DIR[D][DIR_J]))
            {
                t(printf("walk_2 %d\n", D);)
                switch (D)
                {
                    case 0:
                        printf("%s\n", DIR_STR_0);
                        return;
                    case 1:
                        printf("%s\n", DIR_STR_1);
                        return;
                    case 2:
                        printf("%s\n", DIR_STR_2);
                        return;
                    case 3:
                        printf("%s\n", DIR_STR_3);
                        return;
                }
            }
        }
    }

    S32 manhattan_distance_to_rival(
        S32 _pos_i, 
        S32 _pos_j) //t//
    {
        return 
            abs(_pos_i - stats::get().rival_posI) + 
            abs(_pos_j - stats::get().rival_posJ);
    }

    S32 shortest_pathlength_to_rival(
        S32 _pos_i,
        S32 _pos_j)
    {
        vector<vector<vertex> > v_matrix;
        queue<vertex *> v_ref_queue;

        v_matrix.resize(stats::get().map_sizeI);
        for (S32 I = stats::get().map_sizeI; I--;)
            v_matrix[I].resize(stats::get().map_sizeJ);

        v_matrix
            [stats::get().rival_posI]
            [stats::get().rival_posJ]
        = vertex(
            stats::get().rival_posI,
            stats::get().rival_posJ,
            -1, -1,
            0,
            0.0,
            stats::get().rival_flag,
            UNVISITED);

        v_ref_queue.push(
            &v_matrix
                [stats::get().rival_posI]
                [stats::get().rival_posJ]);

        while (! v_ref_queue.empty())
        {
            vertex* NOW = v_ref_queue.front();
            v_ref_queue.pop();

            NOW->state = VISITED;

            if (NOW->pos_i == _pos_i &&
                NOW->pos_j == _pos_j) return NOW->dist;

            for (S32 D = 4; D--;)
            {
                S32 expand_posI = NOW->pos_i + DIR[D][DIR_I];
                S32 expand_posJ = NOW->pos_j + DIR[D][DIR_J];

                if (inbound(expand_posI, expand_posJ) && 
                    stats::get().map
                            [expand_posI]
                            [expand_posJ] != 'x' &&
                    v_matrix
                        [expand_posI]
                        [expand_posJ].state == UNVISITED)
                {
                    v_matrix
                        [expand_posI]
                        [expand_posJ]
                    = vertex(
                        expand_posI,
                        expand_posJ,
                        -1, -1,
                        NOW->dist + 1,
                        0.0,
                        stats::get().map
                            [expand_posI]
                            [expand_posJ],
                        UNVISITED);

                    v_ref_queue.push(
                        &v_matrix
                            [expand_posI]
                            [expand_posJ]);
                }
            }
        }

        return -1;
    }
};

int main()
{
    t(stats::get().print();)
    control::get().walk();

    return 0;
}
