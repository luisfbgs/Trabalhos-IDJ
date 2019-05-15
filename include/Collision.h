#include <algorithm>
#include <cmath>

#include "Rect.h"
#include "Vec2.h"
#include "Common.h"

class Collision {

public:
    static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
        Vec2 A[] = {Vec2(a.lefUp.x, a.lefUp.y + a.h),
                        Vec2(a.lefUp.x + a.w, a.lefUp.y + a.h),
                        Vec2(a.lefUp.x + a.w, a.lefUp.y),
                        Vec2(a.lefUp.x, a.lefUp.y)
                    };
        Vec2 B[] = {Vec2(b.lefUp.x, b.lefUp.y + b.h),
                        Vec2(b.lefUp.x + b.w, b.lefUp.y + b.h),
                        Vec2(b.lefUp.x + b.w, b.lefUp.y),
                        Vec2(b.lefUp.x, b.lefUp.y)
                    };

        for(Vec2& v : A) {
            v = (v - a.Center()).Rotate(angleOfA) + a.Center();
        }

        for(Vec2& v : B) {
            v = (v - b.Center()).Rotate(angleOfB) + b.Center();
        }

        Vec2 axes[] = {(A[0] - A[1]).Norm(), (A[1] - A[2]).Norm(), (B[0] - B[1]).Norm(), (B[1] - B[2]).Norm()};

        for(Vec2& axis : axes) {
            float P[4];

            for(int i = 0; i < 4; ++i) P[i] = A[i] * axis;

            float minA = *std::min_element(P, P + 4);
            float maxA = *std::max_element(P, P + 4);

            for(int i = 0; i < 4; ++i) P[i] = B[i] * axis;

            float minB = *std::min_element(P, P + 4);
            float maxB = *std::max_element(P, P + 4);

            if(maxA <= minB || minA >= maxB)
                return false;
        }

        return true;
    }
};
