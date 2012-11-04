﻿/*
 * Copyright (c) 2010 by Rick Sladkey
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General License for more details.
 * 
 * You should have received a copy of the GNU General License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Sokoban.Engine.Levels;
using Sokoban.Engine.Utilities;

namespace Sokoban.Engine.Solvers
{
    public interface ISolver
    {
        string DeadlocksDirectory { get; set; }
        bool CollectSolutions { get; set; }
        bool CalculateDeadlocks { get; set; }
        bool HardCodedDeadlocks { get; set; }
        Level Level { get; set; }
        int MaximumNodes { get; set; }
        int InitialCapacity { get; set; }
        bool OptimizeMoves { get; set; }
        bool OptimizePushes { get; set; }
        bool DetectNoInfluencePushes { get; set; }
        bool Validate { get; set; }
        bool Verbose { get; set; }
        CancelInfo CancelInfo { get; set; }
        MoveList Solution { get; }
        string Error { get; }
        bool Solve();
    }
}
