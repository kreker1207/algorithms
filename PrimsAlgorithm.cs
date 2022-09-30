using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AlgLab6
{
    using System.Diagnostics;
    using System.Reflection;

    class Edge
    {
        public int Vert1 { get; set; }
        public int Vert2 { get; set; }

        public int Weight { get; set; }

        public Edge(int v1, int v2, int weight)
        {
            Vert1 = v1;
            Vert2 = v2;
            Weight = weight;
        }
    }

    class Graph
    {
        public Graph(int count)
        {
            Count = count;
            Edges = new List<Edge>();
            Matrix = new int[count, count];
        }

        public List<Edge> Edges { get; set; }
        public int Count { get; set; }
        public int[,] Matrix { get; set; }

        public void AddEdge(int v1, int v2, int w)
        {
            var e = new Edge(v1, v2, w);
            this.Edges.Add(e);

            Matrix[v1, v2] = w;
            Matrix[v2, v1] = w;
        }

        public void PrintMatrix()
        {
            var nextFColor = ConsoleColor.Black;
            var nextBColor = ConsoleColor.White;
            Console.Write(String.Format("{0,3}", " ") + " ");
            for (int i = 0; i < Count; i++)
            {
                Console.Write(String.Format("{0,3}", i) + " ");
            }
            Console.WriteLine();
            for (int i = 0; i < Count; i++)
            {
                var t1 = Console.ForegroundColor;
                var t2 = Console.BackgroundColor;
                Console.ForegroundColor = nextFColor;
                Console.BackgroundColor = nextBColor;
                nextFColor = t1;
                nextBColor = t2;
                Console.Write(String.Format("{0,3}", i) + " ");
                for (int j = 0; j < Count; j++)
                {
                    Console.Write(String.Format("{0,3}", Matrix[i, j]) + " ");
                }
                Console.WriteLine();
            }
            Console.ResetColor();
        }

        public static void AlgorithmByPrim(int numberV, List<Edge> E, Graph output)
        {
            List<Edge> MST = new List<Edge>();
            List<Edge> notUsedE = new List<Edge>(E);
            List<int> usedV = new List<int>();
            List<int> notUsedV = new List<int>();
            for (int i = 0; i < numberV; i++)
                notUsedV.Add(i);

            Random rand = new Random();
            usedV.Add(rand.Next(0, numberV));
            notUsedV.RemoveAt(usedV[0]);
            while (notUsedV.Count > 0)
            {
                int minE = -1;
                for (int i = 0; i < notUsedE.Count; i++)
                {
                    if ((usedV.IndexOf(notUsedE[i].Vert1) != -1) && (notUsedV.IndexOf(notUsedE[i].Vert2) != -1) ||
                        (usedV.IndexOf(notUsedE[i].Vert2) != -1) && (notUsedV.IndexOf(notUsedE[i].Vert1) != -1))
                    {
                        if (minE != -1)
                        {
                            if (notUsedE[i].Weight < notUsedE[minE].Weight)
                                minE = i;
                        }
                        else
                            minE = i;
                    }
                }
                if (usedV.IndexOf(notUsedE[minE].Vert1) != -1)
                {
                    usedV.Add(notUsedE[minE].Vert2);
                    notUsedV.Remove(notUsedE[minE].Vert2);
                }
                else
                {
                    usedV.Add(notUsedE[minE].Vert1);
                    notUsedV.Remove(notUsedE[minE].Vert1);
                }
                MST.Add(notUsedE[minE]);
                notUsedE.RemoveAt(minE);
            }

            foreach (var edge in MST)
            {
                output.AddEdge(edge.Vert1, edge.Vert2, edge.Weight);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Input count of vertices: ");
            var countOfVert = Convert.ToInt32(Console.ReadLine());

            var graph = new Graph(countOfVert);
            Console.Write("Input count of edges: ");
            var countOfEdges = Convert.ToInt32(Console.ReadLine());
            for (int i = 0; i < countOfEdges; i++)
            {
                Console.Write($"[Edge {i + 1}/{countOfEdges}] ");
                Console.Write("Input start vertice, end vertice and weight: ");
                var data = Console.ReadLine()?.Split(' ').Select(k => Convert.ToInt32(k)).ToList();
                graph.AddEdge(data[0], data[1], data[2]);
            }

            graph.PrintMatrix();
            Console.WriteLine();
            Graph prim = new Graph(countOfVert);
            Graph.AlgorithmByPrim(countOfVert, graph.Edges, prim);

            Console.WriteLine("Minimum graph after Prim's algorithm: ");
            prim.PrintMatrix();

            Console.ReadKey();
        }
    }
}
