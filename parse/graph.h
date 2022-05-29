enum e_connetion_type
{
	pipex,
	redirect_in,
	redirect_out
};

typedef struct s_node
{
	int				vertex_id;
	int				visited;
	char			*cmd;	
	int				type;
	struct s_node	*next;
}	t_node;

typedef struct s_graph
{
	int		max_vertex_count;
	int		current_vertex_count;
	int		current_edge_count;
	t_node	**edge;
	int		*vertex;
}	t_graph;

t_graph	*create_graph(int max_vertex_count);
void	destroy_graph(t_graph *graph);
int		add_vertex(t_graph *graph, int vertex_id);
int		add_edge(t_graph *graph, int from_vertex_id, \
								int to_vertex_id, int type);

